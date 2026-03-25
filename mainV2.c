#include <stdio.h>
#include <stdbool.h>
#include <time.h>
//#include <windows.h>

/* ─── Constants ─────────────────────────────────────────────────────────── */
#define EMISSION_RICE        4.5f
#define EMISSION_MEAT       30.0f
#define EMISSION_VEG_FRUIT   1.0f
#define CHARGES_PER_KG_CO2 121.7f

/* ─── Structs ────────────────────────────────────────────────────────────── */
typedef struct {
    float total_weight;
    float total_cost;
    float carbon_footprint;
} WasteRecord;

/* ─── Forward Declarations ──────────────────────────────────────────────── */
void run_food_waste_calculator(void);
void run_pm25_review(void);
void run_tax_calculator(void);

void print_food_waste_banner(void);
void print_pm25_banner(void);
void print_main_menu(void);

void handle_food_genre(int genre, WasteRecord *record);
void handle_plate_choice(int genre, float *weight, float *cost);
void print_waste_summary(const WasteRecord *record);
void print_waste_grade(float total_weight);

void print_pm25_summary(float avg_pm, float max_pm);
float calculate_tax(float income);

/* ══════════════════════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════════════════════ */
int main(void)
{
    //SetConsoleOutputCP(CP_UTF8);

    int program = 0;

    while (true) {
        print_main_menu();
        scanf("%d", &program);

        switch (program) {
            case 1: run_food_waste_calculator(); break;
            case 2: run_pm25_review();           break;
            case 3: run_tax_calculator();         break;
            case 0:
                printf("Thank you for using Super Program!\n");
                return 0;
            default:
                printf("Invalid number. Please try again.\n");
                break;
        }
    }
    return 0;
}

/* ══════════════════════════════════════════════════════════════════════════
   MENUS & BANNERS
   ══════════════════════════════════════════════════════════════════════════ */
void print_main_menu(void)
{
    printf("========================\n");
    printf("  Welcome to Super Program\n");
    printf("       Two in One\n");
    printf("========================\n");
    printf("[1] Food Waste Calculator\n");
    printf("[2] PM2.5 Review\n");
    printf("[3] Tax Calculator\n");
    printf("[0] EXIT\n");
    printf("Select: ");
}

void print_food_waste_banner(void)
{
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ ░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓███████▓▒░       ░▒▓████████▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓███████▓▒░ ║\n");
    printf("║░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ ║\n");
    printf("║░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ ║\n");
    printf("║░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓██████▓▒░ ░▒▓█▓▒░▒▓█▓▒▒▓███▓▒░▒▓████████▓▒░  ░▒▓█▓▒░   ░▒▓██████▓▒░ ░▒▓███████▓▒░  ║\n");
    printf("║░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ ║\n");
    printf("║░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ ║\n");
    printf("║░▒▓█▓▒░      ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓███████▓▒░       ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░ ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
}

void print_pm25_banner(void)
{
    printf("░▒▓███████▓▒░░▒▓██████████████▓▒░       ░▒▓████████▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓███████▓▒░\n");
    printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n");
    printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n");
    printf("░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓██████▓▒░ ░▒▓█▓▒░▒▓█▓▒▒▓███▓▒░▒▓████████▓▒░  ░▒▓█▓▒░   ░▒▓██████▓▒░ ░▒▓███████▓▒░\n");
    printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n");
    printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n");
    printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░\n");
}

/* ══════════════════════════════════════════════════════════════════════════
   FOOD WASTE CALCULATOR
   ══════════════════════════════════════════════════════════════════════════ */
void run_food_waste_calculator(void)
{
    WasteRecord record = {0.0f, 0.0f, 0.0f};
    int genre = 0;

    while (true) {
        print_food_waste_banner();

        printf("==== Select Food Genre ====\n");
        printf("[1] Rice/Flour  (60 THB/kg)\n");
        printf("[2] Meat        (200 THB/kg)\n");
        printf("[3] Veg/Fruit   (50 THB/kg)\n");
        printf("[0] Finish\n");
        printf("Your choice: ");
        scanf("%d", &genre);

        if (genre == 0) {
            break;
        } else if (genre < 1 || genre > 3) {
            printf("\n!! Invalid choice. Please enter 1, 2, 3, or 0. !!\n\n");
        } else {
            handle_food_genre(genre, &record);
            printf("Running Total — Food Waste: %.2f kg\n\n", record.total_weight);
        }
    }

    print_waste_summary(&record);
    print_waste_grade(record.total_weight);

    printf("\n=====================================================\n");
    printf("Returning to main menu...\n");
    printf("=====================================================\n");
}

/* Handles one food genre entry and updates the WasteRecord. */
void handle_food_genre(int genre, WasteRecord *record)
{
    const char *genre_names[] = {"", "Rice/Flour", "Meat", "Veg/Fruit"};
    const float emission_factors[] = {0.0f, EMISSION_RICE, EMISSION_MEAT, EMISSION_VEG_FRUIT};
    /* Default price per kg when user enters weight directly */
    const float default_price[] = {0.0f, 70.0f, 150.0f, 40.0f};

    printf("──────────────────────────────────\n");
    printf("Selected: [%s]\n", genre_names[genre]);
    printf("How much did you throw away? (kg)\n");
    printf("(Type 0 if you don't know): ");

    float user_weight = 0.0f;
    scanf("%f", &user_weight);

    float weight = 0.0f;
    float cost   = 0.0f;

    if (user_weight == 0.0f) {
        handle_plate_choice(genre, &weight, &cost);
    } else {
        printf("You threw away %.2f kg.\n", user_weight);
        weight = user_weight;
        cost   = default_price[genre] * weight;
    }

    record->total_weight    += weight;
    record->total_cost      += cost;
    record->carbon_footprint += weight * emission_factors[genre];
}

/* Prompts user to estimate waste by plate fraction and fills weight/cost. */
void handle_plate_choice(int genre, float *weight, float *cost)
{
    /*
     * plate_data[genre][choice][0] = price (THB)
     * plate_data[genre][choice][1] = weight (kg)
     * Indices: genre 1=Rice, 2=Meat, 3=Veg  |  choice 1..4
     */
    const float plate_data[4][5][2] = {
        /* [0] unused */
        {{0,0},{0,0},{0,0},{0,0},{0,0}},
        /* [1] Rice/Flour */
        {{0,0},{70.0f,0.50f},{56.0f,0.40f},{35.0f,0.25f},{14.0f,0.10f}},
        /* [2] Meat */
        {{0,0},{150.0f,0.20f},{120.0f,0.16f},{75.0f,0.10f},{30.0f,0.04f}},
        /* [3] Veg/Fruit */
        {{0,0},{40.0f,0.40f},{32.0f,0.30f},{20.0f,0.20f},{8.0f,0.08f}}
    };

    printf("How much was left on the plate?\n");
    printf("[1] Full plate\n");
    printf("[2] ~80%%\n");
    printf("[3] ~50%%\n");
    printf("[4] ~20%%\n");
    printf("Your choice: ");

    int choice = 0;
    scanf("%d", &choice);

    if (choice < 1 || choice > 4) {
        printf("Invalid choice — no waste recorded for this entry.\n");
        *weight = 0.0f;
        *cost   = 0.0f;
        return;
    }

    *cost   = plate_data[genre][choice][0];
    *weight = plate_data[genre][choice][1];
}

void print_waste_summary(const WasteRecord *record)
{
    printf("\n");
    printf(" ╔══════════════════════════════════════════════════════╗\n");
    printf(" ║              FINAL WASTE ANALYSIS                    ║\n");
    printf(" ╠══════════════════════════════════════════════════════╣\n");
    printf(" ║  Total Food Waste     :   %6.2f kg                  ║\n", record->total_weight);
    printf(" ║  Financial Loss       :   %6.2f THB                 ║\n", record->total_cost);
    printf(" ║  Carbon Footprint     :   %6.2f kgCO2e              ║\n", record->carbon_footprint);
    printf(" ╠══════════════════════════════════════════════════════╣\n");
    printf(" ║  [ Comparisons ]                                     ║\n");
    printf(" ║  Equivalent CO2 absorbed by                          ║\n");
    printf(" ║  >> %6.1f small plants per year                     ║\n", record->carbon_footprint / 0.5f);
    printf(" ║  Charging a smartphone %6.0f times                  ║\n", record->carbon_footprint * CHARGES_PER_KG_CO2);
    printf(" ╚══════════════════════════════════════════════════════╝\n");
}

void print_waste_grade(float total_weight)
{
    const char *grade, *title;

    if      (total_weight <= 0.1f) { grade = "S"; title = "World Protector!"; }
    else if (total_weight <= 0.2f) { grade = "A"; title = "World Lover";      }
    else if (total_weight <= 0.3f) { grade = "B"; title = "Careful Eater";    }
    else if (total_weight <= 0.6f) { grade = "C"; title = "Normal Human";     }
    else if (total_weight <= 1.3f) { grade = "D"; title = "Food Waster";      }
    else                           { grade = "F"; title = "Earth Destroyer";  }

    printf("\n");
    printf(" ╔══════════════════════════════════════════════════════╗\n");
    printf(" ║               FOOD FIGHTER GRADE                     ║\n");
    printf(" ╠══════════════════════════════════════════════════════╣\n");
    printf(" ║  Final Grade          :   %-27s║\n", grade);
    printf(" ║  Rank Title           :   %-27s║\n", title);
    printf(" ╚══════════════════════════════════════════════════════╝\n");
}

/* ══════════════════════════════════════════════════════════════════════════
   PM2.5 REVIEW
   ══════════════════════════════════════════════════════════════════════════ */
void run_pm25_review(void)
{
    print_pm25_banner();
    printf("\nWelcome to PM2.5 Weekly Analysis\n\n");

    const char *days[7] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };

    float pm_values[7];
    float pm_total = 0.0f;
    float pm_max   = 0.0f;

    for (int i = 0; i < 7; i++) {
        printf("PM2.5 on %-10s : ", days[i]);
        scanf("%f", &pm_values[i]);
        pm_total += pm_values[i];
        if (pm_values[i] > pm_max) {
            pm_max = pm_values[i];
        }
    }

    float avg_pm = pm_total / 7.0f;
    print_pm25_summary(avg_pm, pm_max);

    printf("=====================================================\n");
    printf("Returning to main menu...\n");
    printf("=====================================================\n");
}

void print_pm25_summary(float avg_pm, float max_pm)
{
    const char *status, *review_line1, *review_line2;

    if (avg_pm <= 25.0f) {
        status       = "EXCELLENT (Blue)";
        review_line1 = "Great week for your lungs! Air quality was very";
        review_line2 = "good. Perfect for all outdoor activities.";
    } else if (avg_pm <= 50.0f) {
        status       = "GOOD (Green)";
        review_line1 = "Air quality was decent. You can do outdoor";
        review_line2 = "activities normally.";
    } else if (avg_pm <= 100.0f) {
        status       = "MODERATE (Yellow)";
        review_line1 = "Some pollution detected. Reduce heavy cardio";
        review_line2 = "outdoors if you have respiratory issues.";
    } else if (avg_pm <= 200.0f) {
        status       = "UNHEALTHY (Orange)";
        review_line1 = "High pollution week. You might feel irritation.";
        review_line2 = "Wear a mask and avoid outdoor exercise.";
    } else {
        status       = "HAZARDOUS (Red)";
        review_line1 = "CRITICAL EXPOSURE! Dangerous levels detected.";
        review_line2 = "Stay indoors and check your health if unwell.";
    }

    printf("\n");
    printf(" ╔══════════════════════════════════════════════════════╗\n");
    printf(" ║              PM2.5 WEEKLY ANALYSIS                   ║\n");
    printf(" ╠══════════════════════════════════════════════════════╣\n");
    printf(" ║  Average PM2.5        :   %-27.2f║\n", avg_pm);
    printf(" ║  Highest PM2.5        :   %-27.2f║\n", max_pm);
    printf(" ║  Status               :   %-27s║\n", status);
    printf(" ╠══════════════════════════════════════════════════════╣\n");
    printf(" ║  [ Health Review ]                                   ║\n");
    printf(" ║  %-52s║\n", review_line1);
    printf(" ║  %-52s║\n", review_line2);
    printf(" ╚══════════════════════════════════════════════════════╝\n");
}

/* ══════════════════════════════════════════════════════════════════════════
   TAX CALCULATOR
   ══════════════════════════════════════════════════════════════════════════ */

/* Returns Thai personal income tax for the given annual income (THB). */
float calculate_tax(float income)
{
    if      (income <= 150000.0f)  return 0.0f;
    else if (income <= 300000.0f)  return (income - 150000.0f) * 0.05f;
    else if (income <= 500000.0f)  return 7500.0f   + (income - 300000.0f) * 0.10f;
    else if (income <= 750000.0f)  return 27500.0f  + (income - 500000.0f) * 0.15f;
    else if (income <= 1000000.0f) return 65000.0f  + (income - 750000.0f) * 0.20f;
    else if (income <= 2000000.0f) return 115000.0f + (income - 1000000.0f) * 0.25f;
    else if (income <= 5000000.0f) return 365000.0f + (income - 2000000.0f) * 0.30f;
    else                           return 1265000.0f + (income - 5000000.0f) * 0.35f;
}

void run_tax_calculator(void)
{
    printf("\n=== Thai Personal Income Tax Calculator ===\n");
    printf("Enter your annual income (THB): ");

    float income = 0.0f;
    scanf("%f", &income);

    float tax = calculate_tax(income);

    printf("\n");
    printf(" ╔══════════════════════════════════════════════════════╗\n");
    printf(" ║               TAX CALCULATION RESULT                 ║\n");
    printf(" ╠══════════════════════════════════════════════════════╣\n");
    printf(" ║  Annual Income        :   %10.2f THB             ║\n", income);
    printf(" ║  Tax Payable          :   %10.2f THB             ║\n", tax);
    printf(" ╚══════════════════════════════════════════════════════╝\n");

    printf("\n=====================================================\n");
    printf("Returning to main menu...\n");
    printf("=====================================================\n");
}