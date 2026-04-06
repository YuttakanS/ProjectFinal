#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

#define Emission_Factor_Rice 4.5
#define Emission_Factor_Meat 30
#define Emission_Factor_Veg_Fruit 1
#define CHARGES_PER_KGCO2 121.7
#define MAX_PM25_RECORDS 50

// ============================================================
// Prototypes
// ============================================================
void print_food_waste_banner(void);
void print_pm25_banner(void);
void print_main_menu(void);

void run_food_waste_calculator(void);
void run_pm25_review(void);
void run_tax_calculator(void);

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
            case 0:
                printf("Exiting...\n");
                Sleep(2000);
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}


// ============================================================
// Main Menu
// ============================================================
void print_main_menu(void){
    printf("========================\n");
    printf("Welcome to Super Program\n");
    printf("========================\n");
    printf("[1] Food Waste Calculator\n");
    printf("[2] PM2.5 Review\n");
    printf("[3] Tax Calculator\n");
    printf("[0] EXIT\n");
    printf("Select: ");
}


// ============================================================
// Food Waste Calculator
// ============================================================
void print_food_waste_banner(void){
    printf("╔════════════════════════════════════════╗\n");
    printf("║      Food Waste Calculator             ║\n");
    printf("╚════════════════════════════════════════╝\n");
}

void run_food_waste_calculator(void){
    float Totalwaste        = 0;
    float curent_money_waste = 0;
    float cabonfootprint    = 0;
    int   ChoiceZero        = 0;
    float User_Waste        = 0;

    print_food_waste_banner();
    printf("Welcome to Food Waste Calculator\n\n");
    Sleep(2000);

    while(true){
        printf("╔════════════════════════════════════════╗\n");
        printf("║            Food Waste Calculator       ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("1. Add Food Waste\n");
        printf("2. View Results\n");
        printf("3. Reset Calculator\n");
        printf("0. Back to Main Menu\n");
        printf("Select: ");
        scanf("%d", &ChoiceZero);

        switch(ChoiceZero){
            case 1:
                printf("Enter the amount of food waste (in kg): ");
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
                printf("Calculator has been reset.\n");
                break;
            case 0:
                return;
            default:
                printf("Invalid option. Please try again.\n");
                printf("try again after 3 seconds...\n");
                Sleep(3000);
        }
    }
}

void food_waste_sumary(float Totalwaste, float curent_money_waste, float cabonfootprint){
    printf("\n");
    printf(" ╔══════════════════════════════════════════════════════╗\n");
    printf(" ║                FINAL WASTE ANALYSIS                  ║\n");
    printf(" ╠═════════════════════════════════════════════════════╣\n");
    printf(" ║  Total Food Waste     :   %6.2f Kg                  ║\n", Totalwaste);
    printf(" ║  Financial Loss       :   %6.2f THB                ║\n", curent_money_waste);
    printf(" ║  Carbon Footprint     :   %6.2f kgCO2e              ║\n", cabonfootprint);
    printf(" ╠══════════════════════════════════════════════════════╣\n");
    printf(" ║  [ compare ]                                         ║\n");
    printf(" ║  Your waste equals to the CO2 absorption of          ║\n");
    printf(" ║  >> %6.1f small plants per year!                    ║\n", cabonfootprint / 0.5);
    printf(" ║  Charging a smartphone %6.0f times                 ║\n", cabonfootprint * CHARGES_PER_KGCO2);
    printf(" ╚══════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(" ╔══════════════════════════════════════════════════════╗\n");
    printf(" ║                 FOOD FIGHTER GRADE                   ║\n");
    printf(" ╠══════════════════════════════════════════════════════╣\n");

    if      (Totalwaste <= 0.1){
        printf(" ║  Final Grade          :   %-27s║\n", "S");
        printf(" ║  Rank Title           :   %-27s║\n", "World Protector!");
    } else if (Totalwaste <= 0.2){
        printf(" ║  Final Grade          :   %-27s║\n", "A");
        printf(" ║  Rank Title           :   %-27s║\n", "World Lover");
    } else if (Totalwaste <= 0.3){
        printf(" ║  Final Grade          :   %-27s║\n", "B");
        printf(" ║  Rank Title           :   %-27s║\n", "Careful Eater");
    } else if (Totalwaste <= 0.6){
        printf(" ║  Final Grade          :   %-27s║\n", "C");
        printf(" ║  Rank Title           :   %-27s║\n", "Normal Human");
    } else if (Totalwaste <= 1.3){
        printf(" ║  Final Grade          :   %-27s║\n", "D");
        printf(" ║  Rank Title           :   %-27s║\n", "Food Waster");
    } else {
        printf(" ║  Final Grade          :   %-27s║\n", "F");
        printf(" ║  Rank Title           :   %-27s║\n", "Earth Destroyer");
    }

    printf(" ╚══════════════════════════════════════════════════════╝\n");
    printf("\n=====================================================\n");
    printf("Returning to food waste menu...\n");
    printf("=====================================================\n");
    Sleep(3000);
}


// ============================================================
// PM2.5 Review
// ============================================================
void print_pm25_banner(void){
    printf("╔════════════════════════════════════════╗\n");
    printf("║          PM2.5 Review                  ║\n");
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
        printf("║            PM2.5 Review                ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("1. บันทึกค่า PM2.5\n");
        printf("2. วิเคราะห์ค่าปัจจุบัน (ไม่บันทึก)\n");
        printf("3. ดูประวัติค่าที่บันทึก\n");
        printf("4. ดูสรุปและค่าเฉลี่ย\n");
        printf("0. Back to Main Menu\n");
        printf("Select: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                pm25_input(records, &count);
                break;
            case 2: {
                float val = 0;
                printf("Enter PM2.5 value (µg/m³): ");
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
                printf("Returning to main menu...\n");
                printf("=====================================================\n");
                Sleep(2000);
                return;
            default:
                printf("Invalid option. Please try again.\n");
                Sleep(2000);
        }
    }
}

void pm25_input(float records[], int *count){
    if(*count >= MAX_PM25_RECORDS){
        printf("[ ERROR ] บันทึกเต็มแล้ว (สูงสุด %d รายการ)\n", MAX_PM25_RECORDS);
        Sleep(2000);
        return;
    }

    float val = 0;
    printf("Enter PM2.5 value (µg/m³): ");
    scanf("%f", &val);

    if(val < 0){
        printf("[ ERROR ] ค่า PM2.5 ต้องไม่ติดลบ\n");
        Sleep(2000);
        return;
    }

    records[*count] = val;
    (*count)++;

    printf("[ OK ] บันทึกค่า %.2f µg/m³ แล้ว (รายการที่ %d)\n", val, *count);
    Sleep(1000);
    pm25_analyze(val);
}

void pm25_analyze(float value){
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║               PM2.5 ANALYSIS                         ║\n");
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  PM2.5 Value   :  %8.2f µg/m³                   ║\n", value);
    printf("║  Level         :  %-34s║\n", pm25_get_level_name(value));
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  Advice        :  %-34s║\n", pm25_get_advice(value));
    printf("╚══════════════════════════════════════════════════════╝\n\n");
    Sleep(1500);
}

const char* pm25_get_level_name(float value){
    if      (value <= 25) return "Good           (ดี)";
    else if (value <= 37) return "Moderate       (ปานกลาง)";
    else if (value <= 50) return "Unhealthy      (มีผลต่อสุขภาพ)";
    else if (value <= 90) return "Very Unhealthy (เริ่มอันตราย)";
    else                  return "Hazardous      (อันตรายมาก)";
}

const char* pm25_get_advice(float value){
    if      (value <= 25) return "ออกกำลังกายกลางแจ้งได้ตามปกติ  ";
    else if (value <= 37) return "ผู้ป่วยควรลดกิจกรรมกลางแจ้ง   ";
    else if (value <= 50) return "ทุกคนควรลดกิจกรรมกลางแจ้ง     ";
    else if (value <= 90) return "ใส่ N95 / หลีกเลี่ยงออกนอกบ้าน";
    else                  return "ห้ามออกนอกบ้าน! ปิดประตูทันที  ";
}

void pm25_show_history(float records[], int count){
    if(count == 0){
        printf("[ INFO ] ยังไม่มีข้อมูล กรุณาบันทึกค่าก่อน\n");
        Sleep(2000);
        return;
    }

    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║                  PM2.5 HISTORY                       ║\n");
    printf("╠════╦══════════════╦═══════════════════════════════════╣\n");
    printf("║ No ║    Value     ║  Level                           ║\n");
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
        printf("[ INFO ] ยังไม่มีข้อมูล กรุณาบันทึกค่าก่อน\n");
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
    printf("║               PM2.5 SUMMARY                          ║\n");
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  Total Records :  %-34d║\n", count);
    printf("║  Average       :  %-6.2f µg/m³  %-21s║\n", avg,     pm25_get_level_name(avg));
    printf("║  Maximum       :  %-6.2f µg/m³  %-21s║\n", max_val, pm25_get_level_name(max_val));
    printf("║  Minimum       :  %-6.2f µg/m³  %-21s║\n", min_val, pm25_get_level_name(min_val));
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  Overall Advice:  %-34s║\n", pm25_get_advice(avg));
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
        printf("║           Tax Calculator               ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("1. Personal Income Tax (ภาษีเงินได้บุคคลธรรมดา)\n");
        printf("2. VAT Calculator (ภาษีมูลค่าเพิ่ม 7%%)\n");
        printf("0. Back to Main Menu\n");
        printf("Select: ");
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
                printf("║    Personal Income Tax Calculator      ║\n");
                printf("╚════════════════════════════════════════╝\n");

                printf("Enter annual income (รายได้ต่อปี) in THB: ");
                scanf("%f", &annual_income);

                deduction_work = annual_income * 0.50f;
                if(deduction_work > 100000) deduction_work = 100000;

                printf("Enter additional deductions (ค่าลดหย่อนเพิ่มเติม) in THB: ");
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
                printf("║         VAT Calculator (7%%)            ║\n");
                printf("╚════════════════════════════════════════╝\n");
                printf("1. คำนวณ VAT จากราคาที่ยังไม่รวม VAT\n");
                printf("2. ถอด VAT จากราคาที่รวม VAT แล้ว\n");
                printf("Select: ");
                scanf("%d", &vat_choice);

                if(vat_choice == 1){
                    printf("Enter price (ราคาไม่รวม VAT) in THB: ");
                    scanf("%f", &price);
                    float vat_amount = price * 0.07f;
                    float total      = price + vat_amount;
                    tax_calculator_summary(2, 0,0,0,0,0,0,0, price, vat_amount, total, vat_choice);
                } else if(vat_choice == 2){
                    printf("Enter price (ราคารวม VAT แล้ว) in THB: ");
                    scanf("%f", &price);
                    float price_ex_vat = price / 1.07f;
                    float vat_amount   = price - price_ex_vat;
                    tax_calculator_summary(2, 0,0,0,0,0,0,0, price, vat_amount, price_ex_vat, vat_choice);
                } else {
                    printf("Invalid option.\n");
                    Sleep(2000);
                }
                break;
            }

            case 0:
                printf("\n=====================================================\n");
                printf("Returning to main menu...\n");
                printf("=====================================================\n");
                Sleep(2000);
                return;

            default:
                printf("Invalid option. Please try again.\n");
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
        printf("║            INCOME TAX SUMMARY                        ║\n");
        printf("╠══════════════════════════════════════════════════════╣\n");
        printf("║  Annual Income        :  %10.2f THB             ║\n", annual_income);
        printf("║  Deduction (Work 50%%) :  %10.2f THB             ║\n", deduction_work);
        printf("║  Deduction (Personal) :  %10.2f THB             ║\n", deduction_personal);
        printf("║  Deduction (Extra)    :  %10.2f THB             ║\n", deduction_extra);
        printf("║  Total Deductions     :  %10.2f THB             ║\n", total_deduction);
        printf("╠══════════════════════════════════════════════════════╣\n");
        printf("║  Net Taxable Income   :  %10.2f THB             ║\n", net_income);
        printf("║  Tax to Pay           :  %10.2f THB             ║\n", tax);
        printf("║  Effective Tax Rate   :  %9.2f %%              ║\n",
               annual_income > 0 ? (tax / annual_income * 100) : 0);
        printf("╚══════════════════════════════════════════════════════╝\n");

    } else if(mode == 2){
        printf("\n╔══════════════════════════════════════════════════════╗\n");
        printf("║                  VAT SUMMARY                         ║\n");
        printf("╠══════════════════════════════════════════════════════╣\n");
        if(vat_choice == 1){
            printf("║  Price (ex-VAT)       :  %10.2f THB             ║\n", price);
            printf("║  VAT 7%%               :  %10.2f THB             ║\n", vat_amount);
            printf("║  Total (inc-VAT)      :  %10.2f THB             ║\n", price2);
        } else {
            printf("║  Total (inc-VAT)      :  %10.2f THB             ║\n", price);
            printf("║  VAT 7%%               :  %10.2f THB             ║\n", vat_amount);
            printf("║  Price (ex-VAT)       :  %10.2f THB             ║\n", price2);
        }
        printf("╚══════════════════════════════════════════════════════╝\n");
    }

    printf("\n=====================================================\n");
    printf("Returning to tax menu...\n");
    printf("=====================================================\n");
    Sleep(2000);
}