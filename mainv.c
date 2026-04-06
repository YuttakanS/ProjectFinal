#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define Emission_Factor_Rice 4.5
#define Emission_Factor_Meat 30
#define Emission_Factor_Veg_Fruit 1
#define CHARGES_PER_KGCO2 121.7
#define MAX_PM25_RECORDS 50
#define LANG_MAX 3

// ============================================================
// Global Language
// ============================================================
char current_lang[LANG_MAX] = "EN";

const char* lang_str(const char *en_text, const char *th_text){
    if(strcmp(current_lang, "TH") == 0) return th_text;
    return en_text;
}
void lang_set(const char *lang){
    if(strlen(lang) == 0 || strlen(lang) >= LANG_MAX){
        printf("[ ERROR ] Invalid language code.\n");
        return;
    }
    strcpy(current_lang, lang);
}


// ============================================================
// Prototypes
// ============================================================
void print_food_waste_banner(void);
void print_pm25_banner(void);
void print_main_menu(void);

void run_food_waste_calculator(void);
void run_pm25_review(void);
void run_tax_calculator(void);
void run_language_settings(void);

void food_waste_sumary(float Totalwaste, float curent_money_waste, float cabonfootprint);
void tax_calculator_summary(int mode, float annual_income, float deduction_work,
                             float deduction_personal, float deduction_extra,
                             float total_deduction, float net_income, float tax,
                             float price, float vat_amount, float price2, int vat_choice);

void pm25_input(float records[], int *count);
void pm25_show_history(float records[], int count);
void pm25_show_summary(float records[], int count);
void pm25_analyze(float value);
const char* pm25_get_level_name(float value);
const char* pm25_get_advice(float value);


// ============================================================
// Main
// ============================================================
int main(){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    while(true){
        int program = 0;
        print_main_menu();
        scanf("%d", &program);
        switch(program){
            case 1: run_food_waste_calculator(); break;
            case 2: run_pm25_review();           break;
            case 3: run_tax_calculator();        break;
            case 4: run_language_settings();     break;
            case 0:
                printf("%s\n", lang_str("Exiting...", "กำลังออกจากโปรแกรม..."));
                Sleep(2000);
                return 0;
            default:
                printf("%s\n", lang_str("Invalid option. Please try again.",
                                        "ตัวเลือกไม่ถูกต้อง กรุณาลองใหม่"));
        }
    }
}


// ============================================================
// Main Menu
// ============================================================
void print_main_menu(void){
    printf("================================\n");
    printf("%s\n", lang_str("Welcome to Super Program",
                            "ยินดีต้อนรับสู่ Super Program"));
    printf("================================\n");
    printf("%s\n", lang_str("[1] Food Waste Calculator", "[1] คำนวณขยะอาหาร"));
    printf("%s\n", lang_str("[2] PM2.5 Review",          "[2] ตรวจสอบค่า PM2.5"));
    printf("%s\n", lang_str("[3] Tax Calculator",        "[3] คำนวณภาษี"));
    printf("%s\n", lang_str("[4] Language / ภาษา",       "[4] Language / ภาษา"));
    printf("%s\n", lang_str("[0] EXIT",                  "[0] ออกจากโปรแกรม"));
    printf("%s: ",  lang_str("Select",                   "เลือก"));
}


// ============================================================
// Language Settings
// ============================================================
void run_language_settings(void){
    int choice = 0;
    printf("╔════════════════════════════════════════╗\n");
    printf("║       Language Settings / ภาษา        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("%s : %s\n", lang_str("Current Language", "ภาษาปัจจุบัน"), current_lang);
    printf("----------------------------------------\n");
    printf("1. English (EN)\n");
    printf("2. ภาษาไทย (TH)\n");
    printf("0. %s\n", lang_str("Back", "กลับ"));
    printf("%s: ", lang_str("Select", "เลือก"));
    scanf("%d", &choice);

    switch(choice){
        case 1:
            lang_set("EN");
            printf("[ OK ] Language changed to English\n");
            Sleep(1500); break;
        case 2:
            lang_set("TH");
            printf("[ OK ] เปลี่ยนภาษาเป็น ภาษาไทย แล้ว\n");
            Sleep(1500); break;
        case 0:
            return;
        default:
            printf("%s\n", lang_str("Invalid option.", "ตัวเลือกไม่ถูกต้อง"));
            Sleep(2000);
    }
}


// ============================================================
// Food Waste Calculator
// ============================================================
void print_food_waste_banner(void){
    printf("╔════════════════════════════════════════╗\n");
    printf("║  %s  ║\n", lang_str("Food Waste Calculator           ",
                                   "คำนวณขยะอาหาร                   "));
    printf("╚════════════════════════════════════════╝\n");
}

void run_food_waste_calculator(void){
    float Totalwaste         = 0;
    float curent_money_waste = 0;
    float cabonfootprint     = 0;
    int   ChoiceZero         = 0;
    float User_Waste         = 0;

    print_food_waste_banner();
    printf("%s\n\n", lang_str("Welcome to Food Waste Calculator",
                              "ยินดีต้อนรับสู่ระบบคำนวณขยะอาหาร"));
    Sleep(2000);

    while(true){
        printf("╔════════════════════════════════════════╗\n");
        printf("║  %s  ║\n", lang_str("Food Waste Calculator           ",
                                       "คำนวณขยะอาหาร                   "));
        printf("╚════════════════════════════════════════╝\n");
        printf("1. %s\n", lang_str("Add Food Waste",    "เพิ่มขยะอาหาร"));
        printf("2. %s\n", lang_str("View Results",      "ดูผลลัพธ์"));
        printf("3. %s\n", lang_str("Reset Calculator",  "รีเซตค่า"));
        printf("0. %s\n", lang_str("Back to Main Menu", "กลับเมนูหลัก"));
        printf("%s: ", lang_str("Select", "เลือก"));
        scanf("%d", &ChoiceZero);

        switch(ChoiceZero){
            case 1:
                printf("%s (kg): ", lang_str("Enter the amount of food waste",
                                             "กรอกปริมาณขยะอาหาร"));
                scanf("%f", &User_Waste);
                curent_money_waste += User_Waste * 50;
                cabonfootprint     += User_Waste * 2;
                Totalwaste         += User_Waste;
                break;
            case 2:
                food_waste_sumary(Totalwaste, curent_money_waste, cabonfootprint);
                break;
            case 3:
                Totalwaste         = 0;
                curent_money_waste = 0;
                cabonfootprint     = 0;
                printf("%s\n", lang_str("Calculator has been reset.",
                                        "รีเซตค่าเรียบร้อยแล้ว"));
                break;
            case 0:
                return;
            default:
                printf("%s\n", lang_str("Invalid option. Please try again.",
                                        "ตัวเลือกไม่ถูกต้อง กรุณาลองใหม่"));
                Sleep(3000);
        }
    }
}

void food_waste_sumary(float Totalwaste, float curent_money_waste, float cabonfootprint){
    printf("\n");
    printf(" ╔══════════════════════════════════════════════════════╗\n");
    printf(" ║  %s  ║\n", lang_str("           FINAL WASTE ANALYSIS               ",
                                    "           สรุปผลการวิเคราะห์ขยะอาหาร        "));
    printf(" ╠═════════════════════════════════════════════════════╣\n");
    printf(" ║  %-22s :   %6.2f Kg                  ║\n",
           lang_str("Total Food Waste", "ขยะอาหารรวม"), Totalwaste);
    printf(" ║  %-22s :   %6.2f THB                ║\n",
           lang_str("Financial Loss", "มูลค่าที่สูญเสีย"), curent_money_waste);
    printf(" ║  %-22s :   %6.2f kgCO2e              ║\n",
           lang_str("Carbon Footprint", "คาร์บอนฟุตพริ้นท์"), cabonfootprint);
    printf(" ╠══════════════════════════════════════════════════════╣\n");
    printf(" ║  [ %s ]                                   ║\n",
           lang_str("Compare", "เปรียบเทียบ"));
    printf(" ║  %s          ║\n",
           lang_str("Your waste equals CO2 absorption of   ",
                    "ขยะของคุณเทียบเท่า CO2 ที่ต้นไม้ดูดซับ"));
    printf(" ║  >> %6.1f %s                    ║\n",
           cabonfootprint / 0.5,
           lang_str("small plants per year!", "ต้นเล็กต่อปี!           "));
    printf(" ║  %s %6.0f %s                 ║\n",
           lang_str("Charging a smartphone", "ชาร์จสมาร์ทโฟน"),
           cabonfootprint * CHARGES_PER_KGCO2,
           lang_str("times", "ครั้ง "));
    printf(" ╚══════════════════════════════════════════════════════╝\n\n");

    printf(" ╔══════════════════════════════════════════════════════╗\n");
    printf(" ║  %s  ║\n", lang_str("              FOOD FIGHTER GRADE              ",
                                    "              ระดับนักสู้ขยะอาหาร            "));
    printf(" ╠══════════════════════════════════════════════════════╣\n");

    const char *grade, *title;
    if      (Totalwaste <= 0.1){ grade = "S"; title = lang_str("World Protector!", "ผู้พิทักษ์โลก!"); }
    else if (Totalwaste <= 0.2){ grade = "A"; title = lang_str("World Lover",      "คนรักโลก");       }
    else if (Totalwaste <= 0.3){ grade = "B"; title = lang_str("Careful Eater",    "คนกินระวัง");     }
    else if (Totalwaste <= 0.6){ grade = "C"; title = lang_str("Normal Human",     "คนทั่วไป");       }
    else if (Totalwaste <= 1.3){ grade = "D"; title = lang_str("Food Waster",      "ผู้สร้างขยะ");    }
    else                       { grade = "F"; title = lang_str("Earth Destroyer",  "ผู้ทำลายโลก");   }

    printf(" ║  %-22s :   %-27s║\n", lang_str("Final Grade", "เกรด"), grade);
    printf(" ║  %-22s :   %-27s║\n", lang_str("Rank Title",  "ตำแหน่ง"), title);
    printf(" ╚══════════════════════════════════════════════════════╝\n");

    printf("\n=====================================================\n");
    printf("%s\n", lang_str("Returning to food waste menu...",
                            "กำลังกลับสู่เมนูขยะอาหาร..."));
    printf("=====================================================\n");
    Sleep(3000);
}


// ============================================================
// PM2.5 Review
// ============================================================
void print_pm25_banner(void){
    printf("╔════════════════════════════════════════╗\n");
    printf("║  %s  ║\n", lang_str("PM2.5 Review                            ",
                                   "ตรวจสอบค่า PM2.5                        "));
    printf("╚════════════════════════════════════════╝\n");
}

void run_pm25_review(void){
    float records[MAX_PM25_RECORDS];
    int   count  = 0;
    int   choice = 0;

    print_pm25_banner();
    Sleep(1000);

    while(true){
        printf("╔════════════════════════════════════════╗\n");
        printf("║  %s  ║\n", lang_str("PM2.5 Review                            ",
                                       "ตรวจสอบค่า PM2.5                        "));
        printf("╚════════════════════════════════════════╝\n");
        printf("1. %s\n", lang_str("Record PM2.5 value",        "บันทึกค่า PM2.5"));
        printf("2. %s\n", lang_str("Analyze value (no record)", "วิเคราะห์ค่า (ไม่บันทึก)"));
        printf("3. %s\n", lang_str("View history",              "ดูประวัติ"));
        printf("4. %s\n", lang_str("View summary & average",    "ดูสรุปและค่าเฉลี่ย"));
        printf("0. %s\n", lang_str("Back to Main Menu",         "กลับเมนูหลัก"));
        printf("%s: ", lang_str("Select", "เลือก"));
        scanf("%d", &choice);

        switch(choice){
            case 1:
                pm25_input(records, &count);
                break;
            case 2: {
                float val = 0;
                printf("%s (µg/m³): ", lang_str("Enter PM2.5 value", "กรอกค่า PM2.5"));
                scanf("%f", &val);
                pm25_analyze(val);
                break;
            }
            case 3:
                pm25_show_history(records, count);
                break;
            case 4:
                pm25_show_summary(records, count);
                break;
            case 0:
                printf("\n=====================================================\n");
                printf("%s\n", lang_str("Returning to main menu...",
                                        "กำลังกลับสู่เมนูหลัก..."));
                printf("=====================================================\n");
                Sleep(2000);
                return;
            default:
                printf("%s\n", lang_str("Invalid option. Please try again.",
                                        "ตัวเลือกไม่ถูกต้อง กรุณาลองใหม่"));
                Sleep(2000);
        }
    }
}

void pm25_input(float records[], int *count){
    if(*count >= MAX_PM25_RECORDS){
        printf("[ ERROR ] %s (%s %d)\n",
               lang_str("Storage full!", "พื้นที่เต็มแล้ว!"),
               lang_str("Max", "สูงสุด"), MAX_PM25_RECORDS);
        Sleep(2000);
        return;
    }
    float val = 0;
    printf("%s (µg/m³): ", lang_str("Enter PM2.5 value", "กรอกค่า PM2.5"));
    scanf("%f", &val);

    if(val < 0){
        printf("[ ERROR ] %s\n", lang_str("Value cannot be negative.",
                                          "ค่าต้องไม่ติดลบ"));
        Sleep(2000);
        return;
    }
    records[*count] = val;
    (*count)++;
    printf("[ OK ] %s %.2f µg/m³ (%s %d)\n",
           lang_str("Recorded", "บันทึกค่า"), val,
           lang_str("Record no.", "รายการที่"), *count);
    Sleep(1000);
    pm25_analyze(val);
}

void pm25_analyze(float value){
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║  %s  ║\n", lang_str("             PM2.5 ANALYSIS                   ",
                                   "             วิเคราะห์ค่า PM2.5              "));
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  %-16s :  %8.2f µg/m³                   ║\n",
           lang_str("PM2.5 Value", "ค่า PM2.5"), value);
    printf("║  %-16s :  %-34s║\n",
           lang_str("Level", "ระดับ"), pm25_get_level_name(value));
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  %-16s :  %-34s║\n",
           lang_str("Advice", "คำแนะนำ"), pm25_get_advice(value));
    printf("╚══════════════════════════════════════════════════════╝\n\n");
    Sleep(1500);
}

const char* pm25_get_level_name(float value){
    if      (value <= 25) return lang_str("Good           (Healthy)",      "ดี            (สุขภาพดี)");
    else if (value <= 37) return lang_str("Moderate       (Acceptable)",   "ปานกลาง       (พอรับได้)");
    else if (value <= 50) return lang_str("Unhealthy      (Sensitive)",    "มีผลต่อสุขภาพ (กลุ่มเสี่ยง)");
    else if (value <= 90) return lang_str("Very Unhealthy (Dangerous)",    "อันตราย       (เริ่มอันตราย)");
    else                  return lang_str("Hazardous      (Very Danger!)", "อันตรายมาก    (อันตรายสูง!)");
}

const char* pm25_get_advice(float value){
    if      (value <= 25) return lang_str("Outdoor activities are safe.",         "ออกกำลังกายกลางแจ้งได้ตามปกติ  ");
    else if (value <= 37) return lang_str("Sensitive groups reduce outdoors.",    "ผู้ป่วยควรลดกิจกรรมกลางแจ้ง   ");
    else if (value <= 50) return lang_str("Everyone reduce outdoor activity.",    "ทุกคนควรลดกิจกรรมกลางแจ้ง     ");
    else if (value <= 90) return lang_str("Wear N95 / Avoid going outside.",      "ใส่ N95 / หลีกเลี่ยงออกนอกบ้าน");
    else                  return lang_str("Stay indoors! Close windows now!",     "ห้ามออกนอกบ้าน! ปิดประตูทันที  ");
}

void pm25_show_history(float records[], int count){
    if(count == 0){
        printf("[ INFO ] %s\n", lang_str("No records yet. Please record a value first.",
                                         "ยังไม่มีข้อมูล กรุณาบันทึกค่าก่อน"));
        Sleep(2000);
        return;
    }
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║  %s  ║\n", lang_str("                PM2.5 HISTORY                 ",
                                   "              ประวัติค่า PM2.5               "));
    printf("╠════╦══════════════╦═══════════════════════════════════╣\n");
    printf("║ %-2s ║    %-8s  ║  %-33s║\n",
           lang_str("No", "ที่"), lang_str("Value", "ค่า"), lang_str("Level", "ระดับ"));
    printf("╠════╬══════════════╬═══════════════════════════════════╣\n");
    for(int i = 0; i < count; i++){
        printf("║ %2d ║ %7.2f µg/m³║  %-33s║\n",
               i + 1, records[i], pm25_get_level_name(records[i]));
    }
    printf("╚════╩══════════════╩═══════════════════════════════════╝\n\n");
    Sleep(1000);
}

void pm25_show_summary(float records[], int count){
    if(count == 0){
        printf("[ INFO ] %s\n", lang_str("No records yet. Please record a value first.",
                                         "ยังไม่มีข้อมูล กรุณาบันทึกค่าก่อน"));
        Sleep(2000);
        return;
    }
    float sum = 0, max_val = records[0], min_val = records[0];
    for(int i = 0; i < count; i++){
        sum += records[i];
        if(records[i] > max_val) max_val = records[i];
        if(records[i] < min_val) min_val = records[i];
    }
    float avg = sum / count;

    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║  %s  ║\n", lang_str("               PM2.5 SUMMARY                  ",
                                   "               สรุปค่า PM2.5                 "));
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  %-16s :  %-34d║\n", lang_str("Total Records", "จำนวนบันทึก"), count);
    printf("║  %-16s :  %-6.2f µg/m³  %-21s║\n",
           lang_str("Average", "ค่าเฉลี่ย"), avg, pm25_get_level_name(avg));
    printf("║  %-16s :  %-6.2f µg/m³  %-21s║\n",
           lang_str("Maximum", "ค่าสูงสุด"), max_val, pm25_get_level_name(max_val));
    printf("║  %-16s :  %-6.2f µg/m³  %-21s║\n",
           lang_str("Minimum", "ค่าต่ำสุด"), min_val, pm25_get_level_name(min_val));
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  %-16s :  %-34s║\n",
           lang_str("Overall Advice", "คำแนะนำรวม"), pm25_get_advice(avg));
    printf("╚══════════════════════════════════════════════════════╝\n\n");
    Sleep(1500);
}


// ============================================================
// Tax Calculator
// ============================================================
void run_tax_calculator(void){
    while(true){
        int choice = 0;

        printf("╔════════════════════════════════════════╗\n");
        printf("║  %s  ║\n", lang_str("Tax Calculator                          ",
                                       "คำนวณภาษี                               "));
        printf("╚════════════════════════════════════════╝\n");
        printf("1. %s\n", lang_str("Personal Income Tax", "ภาษีเงินได้บุคคลธรรมดา"));
        printf("2. %s\n", lang_str("VAT Calculator (7%)", "ภาษีมูลค่าเพิ่ม (7%)"));
        printf("0. %s\n", lang_str("Back to Main Menu",  "กลับเมนูหลัก"));
        printf("%s: ", lang_str("Select", "เลือก"));
        scanf("%d", &choice);

        switch(choice){
            case 1: {
                float annual_income      = 0;
                float deduction_personal = 60000;
                float deduction_work     = 0;
                float deduction_extra    = 0;
                float net_income         = 0;
                float tax                = 0;

                printf("\n╔════════════════════════════════════════╗\n");
                printf("║  %s  ║\n",
                       lang_str("Personal Income Tax Calculator          ",
                                "คำนวณภาษีเงินได้บุคคลธรรมดา            "));
                printf("╚════════════════════════════════════════╝\n");

                printf("%s (THB): ", lang_str("Enter annual income", "กรอกรายได้ต่อปี"));
                scanf("%f", &annual_income);

                deduction_work = annual_income * 0.50f;
                if(deduction_work > 100000) deduction_work = 100000;

                printf("%s (THB): ", lang_str("Enter additional deductions",
                                              "กรอกค่าลดหย่อนเพิ่มเติม"));
                scanf("%f", &deduction_extra);

                float total_deduction = deduction_personal + deduction_work + deduction_extra;
                net_income = annual_income - total_deduction;
                if(net_income < 0) net_income = 0;

                if      (net_income <= 150000)  tax = 0;
                else if (net_income <= 300000)  tax = (net_income - 150000)  * 0.05f;
                else if (net_income <= 500000)  tax = 7500   + (net_income - 300000)  * 0.10f;
                else if (net_income <= 750000)  tax = 27500  + (net_income - 500000)  * 0.15f;
                else if (net_income <= 1000000) tax = 65000  + (net_income - 750000)  * 0.20f;
                else if (net_income <= 2000000) tax = 115000 + (net_income - 1000000) * 0.25f;
                else if (net_income <= 5000000) tax = 365000 + (net_income - 2000000) * 0.30f;
                else                            tax = 1265000+ (net_income - 5000000) * 0.35f;

                tax_calculator_summary(1, annual_income, deduction_work, deduction_personal,
                                       deduction_extra, total_deduction, net_income, tax,
                                       0, 0, 0, 0);
                break;
            }

            case 2: {
                float price    = 0;
                int vat_choice = 0;

                printf("\n╔════════════════════════════════════════╗\n");
                printf("║  %s  ║\n", lang_str("VAT Calculator (7%)                     ",
                                               "คำนวณภาษีมูลค่าเพิ่ม (7%)               "));
                printf("╚════════════════════════════════════════╝\n");
                printf("1. %s\n", lang_str("Add VAT to price (ex-VAT)",
                                           "บวก VAT จากราคาที่ยังไม่รวม VAT"));
                printf("2. %s\n", lang_str("Extract VAT from price (inc-VAT)",
                                           "ถอด VAT จากราคาที่รวม VAT แล้ว"));
                printf("%s: ", lang_str("Select", "เลือก"));
                scanf("%d", &vat_choice);

                if(vat_choice == 1){
                    printf("%s (THB): ", lang_str("Enter price (ex-VAT)",
                                                  "กรอกราคา (ไม่รวม VAT)"));
                    scanf("%f", &price);
                    float vat_amount = price * 0.07f;
                    float total      = price + vat_amount;
                    tax_calculator_summary(2, 0,0,0,0,0,0,0, price, vat_amount, total, vat_choice);
                } else if(vat_choice == 2){
                    printf("%s (THB): ", lang_str("Enter price (inc-VAT)",
                                                  "กรอกราคา (รวม VAT แล้ว)"));
                    scanf("%f", &price);
                    float price_ex_vat = price / 1.07f;
                    float vat_amount   = price - price_ex_vat;
                    tax_calculator_summary(2, 0,0,0,0,0,0,0, price, vat_amount, price_ex_vat, vat_choice);
                } else {
                    printf("%s\n", lang_str("Invalid option.", "ตัวเลือกไม่ถูกต้อง"));
                    Sleep(2000);
                }
                break;
            }

            case 0:
                printf("\n=====================================================\n");
                printf("%s\n", lang_str("Returning to main menu...",
                                        "กำลังกลับสู่เมนูหลัก..."));
                printf("=====================================================\n");
                Sleep(2000);
                return;

            default:
                printf("%s\n", lang_str("Invalid option. Please try again.",
                                        "ตัวเลือกไม่ถูกต้อง กรุณาลองใหม่"));
                Sleep(2000);
        }
    }
}

void tax_calculator_summary(int mode,
                             float annual_income, float deduction_work,
                             float deduction_personal, float deduction_extra,
                             float total_deduction, float net_income, float tax,
                             float price, float vat_amount, float price2, int vat_choice){
    if(mode == 1){
        printf("\n╔══════════════════════════════════════════════════════╗\n");
        printf("║  %s  ║\n", lang_str("           INCOME TAX SUMMARY                 ",
                                       "           สรุปผลภาษีเงินได้                 "));
        printf("╠══════════════════════════════════════════════════════╣\n");
        printf("║  %-22s :  %10.2f THB             ║\n",
               lang_str("Annual Income",       "รายได้ต่อปี"),       annual_income);
        printf("║  %-22s :  %10.2f THB             ║\n",
               lang_str("Deduction Work(50%)", "หักค่าใช้จ่าย(50%)"), deduction_work);
        printf("║  %-22s :  %10.2f THB             ║\n",
               lang_str("Deduction Personal",  "ลดหย่อนส่วนตัว"),    deduction_personal);
        printf("║  %-22s :  %10.2f THB             ║\n",
               lang_str("Deduction Extra",     "ลดหย่อนเพิ่มเติม"),  deduction_extra);
        printf("║  %-22s :  %10.2f THB             ║\n",
               lang_str("Total Deductions",    "รวมค่าลดหย่อน"),     total_deduction);
        printf("╠══════════════════════════════════════════════════════╣\n");
        printf("║  %-22s :  %10.2f THB             ║\n",
               lang_str("Net Taxable Income",  "รายได้สุทธิ"),       net_income);
        printf("║  %-22s :  %10.2f THB             ║\n",
               lang_str("Tax to Pay",          "ภาษีที่ต้องชำระ"),   tax);
        printf("║  %-22s :  %9.2f %%              ║\n",
               lang_str("Effective Tax Rate",  "อัตราภาษีที่แท้จริง"),
               annual_income > 0 ? (tax / annual_income * 100) : 0);
        printf("╚══════════════════════════════════════════════════════╝\n");

    } else if(mode == 2){
        printf("\n╔══════════════════════════════════════════════════════╗\n");
        printf("║  %s  ║\n", lang_str("               VAT SUMMARY                    ",
                                       "               สรุปผล VAT                    "));
        printf("╠══════════════════════════════════════════════════════╣\n");
        if(vat_choice == 1){
            printf("║  %-22s :  %10.2f THB             ║\n",
                   lang_str("Price (ex-VAT)",  "ราคา (ไม่รวม VAT)"), price);
            printf("║  %-22s :  %10.2f THB             ║\n",
                   lang_str("VAT 7%",          "VAT 7%"),             vat_amount);
            printf("║  %-22s :  %10.2f THB             ║\n",
                   lang_str("Total (inc-VAT)", "ราคา (รวม VAT)"),     price2);
        } else {
            printf("║  %-22s :  %10.2f THB             ║\n",
                   lang_str("Total (inc-VAT)", "ราคา (รวม VAT)"),     price);
            printf("║  %-22s :  %10.2f THB             ║\n",
                   lang_str("VAT 7%",          "VAT 7%"),             vat_amount);
            printf("║  %-22s :  %10.2f THB             ║\n",
                   lang_str("Price (ex-VAT)",  "ราคา (ไม่รวม VAT)"), price2);
        }
        printf("╚══════════════════════════════════════════════════════╝\n");
    }

    printf("\n=====================================================\n");
    printf("%s\n", lang_str("Returning to tax menu...", "กำลังกลับสู่เมนูภาษี..."));
    printf("=====================================================\n");
    Sleep(2000);
}