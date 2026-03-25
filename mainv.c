#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

#define Emission_Factor_Rice 4.5
#define Emission_Factor_Meat 30
#define Emission_Factor_Veg_Fruit 1
#define CHARGES_PER_KGCO2 121.7

void print_food_waste_banner(void);
void print_pm25_banner(void);
void print_main_menu(void);

void run_food_waste_calculator(void);
void run_pm25_review(void);
void print_food_waste_banner(void);
void print_pm25_banner(void);
void food_waste_sumary(float Totalwaste, float curent_money_waste, float cabonfootprint);

int main (){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    while(true){
    int program = 0;
    print_main_menu();
    scanf("%d", &program);
    switch (program)
    {   case 1:
        run_food_waste_calculator();break;       
        case 2:
            run_pm25_review();break;            
        case 3: 
            printf("Tax Calculator is under construction. Please check back later.\n");break;            
        case 0:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
}

void print_main_menu(void){
    printf("========================\n");
    printf("Welcome to Super Program \n");
    printf("Two in One\n");
    printf("========================\n");
    printf("[1] Food Waste Calculator\n");
    printf("[2] PM2.5 Review\n");
    printf("[3] Tax Calculate\n");
    printf("[0] EXIT\n");
    printf("Select: ");
}

void run_food_waste_calculator(void){
    float Totalwaste = 0;
    float curent_money_waste = 0;
    float cabonfootprint = 0;
    int Genre = 0;
    int ChoiceZero = 0;
    float User_Waste = 0;

    print_food_waste_banner();
    printf("Welcome to Food Waste Calculator\n\n");

    while (true)
    {
        printf("╔════════════════════════════════════════╗\n");
        printf("║            Food Waste Calculator       ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("1. Add Food Waste\n");
        printf("2. View Results\n");
        printf("3. Reset Calculator\n");
        printf("0. Back to Main Menu\n");
        printf("Select: ");
        scanf("%d", &ChoiceZero);
        switch (ChoiceZero)
        {
        case 1:
            printf("Enter the amount of food waste (in kg): ");
            scanf("%f", &User_Waste);
            curent_money_waste += User_Waste * 50; // Assuming an average cost of 50 THB/kg
            cabonfootprint += User_Waste * 2; // Assuming an average emission factor of 2 kgCO2e/kg
            Totalwaste += User_Waste;
            break;
        case 2:           
            food_waste_sumary( Totalwaste, curent_money_waste, cabonfootprint);
            break;
        case 3:
            Totalwaste = 0;
            break;
        case 0:
            return;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
}


void run_pm25_review(void){
    print_pm25_banner();
    printf("PM2.5 Review feature is under construction.\n");
    return;
}

void print_food_waste_banner(void){
    printf("╔════════════════════════════════════════╗\n");
    printf("║      Food Waste Calculator             ║\n");
    printf("╚════════════════════════════════════════╝\n");
}

void print_pm25_banner(void){
    printf("╔════════════════════════════════════════╗\n");
    printf("║          PM2.5 Review                  ║\n");
    printf("╚════════════════════════════════════════╝\n");
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

            if (Totalwaste <= 0.1)
            {
                printf(" ║  Final Grade          :   %-27s║\n", "S");                
                printf(" ║  Rank Title           :   %-27s║\n", "World Protector!"); 
            }
            else if (Totalwaste <= 0.2)
            {
                printf(" ║  Final Grade          :   %-27s║\n", "A");           
                printf(" ║  Rank Title           :   %-27s║\n", "World Lover"); 
            }
            else if (Totalwaste <= 0.3)
            {
                printf(" ║  Final Grade          :   %-27s║\n", "B");             
                printf(" ║  Rank Title           :   %-27s║\n", "Careful Eater"); 
            }
            else if (Totalwaste <= 0.6)
            {
                printf(" ║  Final Grade          :   %-27s║\n", "C");            
                printf(" ║  Rank Title           :   %-27s║\n", "Normal Human"); 
            }
            else if (Totalwaste <= 1.3)
            {
                printf(" ║  Final Grade          :   %-27s║\n", "D");           
                printf(" ║  Rank Title           :   %-27s║\n", "Food Waster"); 
            }
            else
            {
                printf(" ║  Final Grade          :   %-27s║\n", "F");               
                printf(" ║  Rank Title           :   %-27s║\n", "Earth Destroyer"); 
            }
            printf(" ╚══════════════════════════════════════════════════════╝\n");

            printf("\n=====================================================\n");
            printf("Returning to main menu...\n");
            printf("=====================================================\n");
            Totalwaste = 0;
            curent_money_waste = 0;
            cabonfootprint = 0;           
    
}
