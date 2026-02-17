#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define Emission_Factor_Rice 4.5
#define Emission_Factor_Meat 30
#define Emission_Factor_Veg_Fruit 1
#define CHARGES_PER_KGCO2 121.7 

int main()
{   
    SetConsoleOutputCP(CP_UTF8);
    int Genre = 0;
    int ChoiceHowWaste = 0;
    float User_Waste = 0;
    float Totalwaste = 0;    
    float TotalMoney = 0;    
    float current_weight = 0;
    float Total_Current_Weight = 0;
    float price_per_kg = 0;
    float curent_money_waste = 0;
    float cabonfootprint =0;
    int program =0;
    float Pm_Value,Pm_Value_Sun,Pm_Value_Mon,Pm_Value_Tues,Pm_Value_Wednes,Pm_Value_Thurs,Pm_Value_Fri,Pm_Value_Satur=0;
    

                                                                                                                                                                                                                                                                                            
    while (true){
            printf("========================\n");
            printf("Welcome to Super Program \n");
            printf("Two in One\n");
            printf("Please select yor program\n");
            printf("[1] Food Waste Calculator\n");
            printf("[2] PM2.5 Review\n");
            printf("[0] EXIT\n");
            scanf("%d",&program);
               switch (program){
               
                case 1:
                    while (true)
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

                        printf("====Select Food genre====\n");
                        printf("[1] Rice/Flour (60 Bath/Kg)\n");
                        printf("[2] Meat (200 Bath/Kg)\n");
                        printf("[3] Veg/Fruit (50 Bath/kg)\n");
                        printf("[0] Exit / Finish\n");                        
                        printf("What is your food genre : ");
                        scanf("%d",&Genre);

                            if (Genre == 0){
                                break;
                            }

                            else if (Genre < 0 || Genre>4){
                                printf("\n\n!!!!!!!!Invalid number. Please check your input number. and try again!!!!!!!! \n");
                            }

                            else {
                                printf("══════════════════════════════════ \n");
                                printf("Ok, Lets calculate it! \n");
                            
                                current_weight = 0;
                                price_per_kg = 0;
                                User_Waste = 0;
                                switch (Genre)
                                {
                                    case 1:{
                                        printf("You have selected [Rice/Flour]\n");
                                        printf("How much did you throw away? (Kg) \n");
                                        printf("If you dont know type [0]\n");
                                        scanf("%f",&User_Waste);
                                            if (User_Waste == 0){
                                                printf("How much it left\n");
                                                printf("[1] Full plate\n");
                                                printf("[2] 80 percent of plate\n");
                                                printf("[3] 50 percent of plate\n");
                                                printf("[4] 20 percent of plate\n");

                                                scanf("%d",&ChoiceHowWaste);
                                                    switch (ChoiceHowWaste){
                                                        case 1:
                                                            price_per_kg = 70;
                                                            current_weight = 0.5; 
                                                            Emission_Factor_Rice;
                                                            break;
                                                        case 2:
                                                            price_per_kg = 56;
                                                            current_weight = 0.4; 
                                                            Emission_Factor_Rice;
                                                            break;
                                                        case 3:
                                                            price_per_kg = 35;
                                                            current_weight = 0.25;
                                                            Emission_Factor_Rice;
                                                            break;
                                                        case 4:
                                                            price_per_kg = 14;
                                                            current_weight = 0.1; 
                                                            Emission_Factor_Rice;
                                                            break;
                                                        default:
                                                            printf("Invalid number \n"); break;     
                                                    }
                                            } 
                                            else {
                                                printf("You throw it away %.2f Kg \n\n",User_Waste);
                                                price_per_kg = 70;
                                                current_weight = User_Waste;
                                            }

                                        Totalwaste += current_weight;
                                        curent_money_waste += (price_per_kg * current_weight); 
                                        cabonfootprint += current_weight * Emission_Factor_Rice;
                                        
                                        printf("Total Food Waste : %.2f Kg \n",Totalwaste);
                                        break;
                                    }

                                    case 2:{
                                        printf("You have selected [Meat]\n");
                                        printf("How much did you throw away? (Kg) \n");
                                        printf("If you dont know type [0]\n");
                                        scanf("%f",&User_Waste);
                                            if (User_Waste == 0){
                                                printf("How much it left\n");
                                                printf("[1] Full plate\n");
                                                printf("[2] 80 percent of plate\n");
                                                printf("[3] 50 percent of plate\n");
                                                printf("[4] 20 percent of plate\n");

                                                scanf("%d",&ChoiceHowWaste);
                                                    switch (ChoiceHowWaste){
                                                        case 1:
                                                            price_per_kg = 150;
                                                            current_weight = 0.2; 
                                                            Emission_Factor_Meat;
                                                            break;
                                                        case 2:
                                                            price_per_kg = 120;
                                                            current_weight = 0.16; 
                                                            Emission_Factor_Meat;
                                                            break;
                                                        case 3:
                                                            price_per_kg = 75;
                                                            current_weight = 0.1; 
                                                            Emission_Factor_Meat;
                                                            break;
                                                        case 4:
                                                            price_per_kg = 30;
                                                            current_weight = 0.04; 
                                                            Emission_Factor_Meat;
                                                            break;
                                                        default:
                                                            printf("Invalid number \n"); break;     
                                                    }
                                            } 
                                            else {
                                                printf("You throw it away %.2f Kg \n\n",User_Waste);
                                                price_per_kg = 150; 
                                                current_weight = User_Waste;
                                            }
                                        Totalwaste += current_weight;
                                        curent_money_waste += (price_per_kg * current_weight);
                                        printf("Total Food Waste : %.2f Kg \n",Totalwaste);
                                        cabonfootprint += current_weight * Emission_Factor_Meat;

                                        break;
                                    }

                                    case 3:{
                                        printf("You have selected [Veg/Fruit]\n");
                                        printf("How much did you throw away? (Kg) \n");
                                        printf("If you dont know type [0]\n");
                                        scanf("%f",&User_Waste);
                                            if (User_Waste == 0){
                                                printf("How much it left\n");
                                                printf("[1] Full plate\n");
                                                printf("[2] 80 percent of plate\n");
                                                printf("[3] 50 percent of plate\n");
                                                printf("[4] 20 percent of plate\n");

                                                scanf("%d",&ChoiceHowWaste);
                                                    switch (ChoiceHowWaste){
                                                        case 1:
                                                            price_per_kg = 40;
                                                            current_weight = 0.4; 
                                                            Emission_Factor_Veg_Fruit;
                                                            break;
                                                        case 2:
                                                            price_per_kg = 32;
                                                            current_weight = 0.3; 
                                                            Emission_Factor_Veg_Fruit;
                                                            break;
                                                            
                                                        case 3:
                                                            price_per_kg = 20;
                                                            current_weight = 0.2; 
                                                            Emission_Factor_Veg_Fruit;
                                                            break;
                                                        case 4:
                                                            price_per_kg = 8;
                                                            current_weight = 0.08; 
                                                            Emission_Factor_Veg_Fruit;
                                                            break;
                                                        default:
                                                            printf("Invalid number \n"); break;     
                                                    }
                                            } 
                                            else {
                                                printf("You throw it away %.2f Kg \n\n",User_Waste);
                                                price_per_kg = 40;
                                                current_weight = User_Waste;
                                            }

                                        Totalwaste += current_weight;
                                        curent_money_waste += (price_per_kg * current_weight);
                                        printf("Total  Food Waste : %.2f Kg \n",Totalwaste);
                                        cabonfootprint += current_weight * Emission_Factor_Veg_Fruit;
                                        break;
                                    }
                                    
                            }
                    }
                }
                

            printf("\n");
            printf(" ╔══════════════════════════════════════════════════════╗\n");
            printf(" ║                FINAL WASTE ANALYSIS                  ║\n");
            printf(" ╠══════════════════════════════════════════════════════╣\n");
            printf(" ║  Total Food Waste     :   %6.2f Kg                  ║\n", Totalwaste);
            printf(" ║  Financial Loss       :   %6.2f THB                 ║\n", curent_money_waste);
            printf(" ║  Carbon Footprint     :   %6.2f kgCO2e              ║\n", cabonfootprint);
            printf(" ╠══════════════════════════════════════════════════════╣\n");
            printf(" ║  [ compare ]                                         ║\n");
            printf(" ║  Your waste equals to the CO2 absorption of          ║\n");           
            printf(" ║  >> %6.1f small plants per year!                    ║\n", cabonfootprint / 0.5);
            printf(" ║  Charging a smartphone %6.0f times                   ║\n", cabonfootprint * CHARGES_PER_KGCO2);
            printf(" ╚══════════════════════════════════════════════════════╝\n");
	        printf("\n");
            printf(" ╔══════════════════════════════════════════════════════╗\n");
            printf(" ║                 FOOD FIGHTER GRADE                   ║\n");
            printf(" ╠══════════════════════════════════════════════════════╣\n");
            
            if (Totalwaste <= 0.1) {
                printf(" ║  Final Grade          :   %-27s║\n", "S");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง                           
                printf(" ║  Rank Title           :   %-27s║\n", "World Protector!");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
            } 
            else if (Totalwaste <= 0.2) {
                printf(" ║  Final Grade          :   %-27s║\n", "A");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
                printf(" ║  Rank Title           :   %-27s║\n", "World Lover");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
            } 
            else if (Totalwaste <= 0.3) {
                printf(" ║  Final Grade          :   %-27s║\n", "B");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
                printf(" ║  Rank Title           :   %-27s║\n", "Careful Eater");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
            } 
            else if (Totalwaste <= 0.6) {
                printf(" ║  Final Grade          :   %-27s║\n", "C");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
                printf(" ║  Rank Title           :   %-27s║\n", "Normal Human");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
            } 
            else if (Totalwaste <= 1.3) {
                printf(" ║  Final Grade          :   %-27s║\n", "D");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
                printf(" ║  Rank Title           :   %-27s║\n", "Food Waster");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
            } 
            else {
                printf(" ║  Final Grade          :   %-27s║\n", "F");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
                printf(" ║  Rank Title           :   %-27s║\n", "Earth Destroyer");// ใช้ %-27s เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
            }
            printf(" ╚══════════════════════════════════════════════════════╝\n");
            
            printf("\n=====================================================\n");
            printf("Returning to main menu...\n");
            printf("=====================================================\n");
            Totalwaste =0;
            curent_money_waste=0;
            cabonfootprint=0;
            break;
        
        /*===============================================================================================================================================*/
        
                case 2:
                            printf("░▒▓███████▓▒░░▒▓██████████████▓▒░       ░▒▓████████▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓███████▓▒░\n");
                            printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n");
                            printf("░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n");
                            printf("░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓██████▓▒░ ░▒▓█▓▒░▒▓█▓▒▒▓███▓▒░▒▓████████▓▒░  ░▒▓█▓▒░   ░▒▓██████▓▒░ ░▒▓███████▓▒░\n");
                            printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n");
                            printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░\n");
                            printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░\n");

                            printf("\nWelcome to PM weekly analysis\n");
                            
                            
                            for (int i = 0; i < 7; i++) {
                                switch (i) {
                                    case 0: 
                                    printf("PM2.5 Level on Sunday    : "); 
                                    scanf("%f", &Pm_Value_Sun); 
                                    break;
                                    case 1: 
                                    printf("PM2.5 Level on Monday    : "); 
                                    scanf("%f", &Pm_Value_Mon); 
                                    break;
                                    case 2: 
                                    printf("PM2.5 Level on Tuesday   : "); 
                                    scanf("%f", &Pm_Value_Tues); 
                                    break;
                                    case 3: 
                                    printf("PM2.5 Level on Wednesday : "); 
                                    scanf("%f", &Pm_Value_Wednes); 
                                    break;
                                    case 4: 
                                    printf("PM2.5 Level on Thursday  : "); 
                                    scanf("%f", &Pm_Value_Thurs); 
                                    break;
                                    case 5: 
                                    printf("PM2.5 Level on Friday    : "); 
                                    scanf("%f", &Pm_Value_Fri); 
                                    break;
                                    case 6: 
                                    printf("PM2.5 Level on Saturday  : "); 
                                    scanf("%f", &Pm_Value_Satur); 
                                    break;
                                    default: break;
                                }
                            }

                            float avg_pm = 0;
                            float pm_total = (Pm_Value_Sun + Pm_Value_Mon + Pm_Value_Tues + Pm_Value_Wednes + Pm_Value_Thurs + Pm_Value_Fri + Pm_Value_Satur);
                            avg_pm = pm_total / 7;

                            float arr[]= {Pm_Value_Sun,Pm_Value_Mon,Pm_Value_Tues,Pm_Value_Wednes,Pm_Value_Thurs,Pm_Value_Fri,Pm_Value_Satur};
                            int n = sizeof(arr)/sizeof(arr[0]);
                            float max =arr[0];
                            

                            for (int i =0; i < n ;i++){
                                if (max < arr[i])
                                    max = arr[i];
                            }
                            
                            for (int i = 0; i < n ; i++){
                                printf("%f",arr[i]);

                            }
                            
                                                     
                            
                            
                            printf("\n");
                            printf(" ╔══════════════════════════════════════════════════════╗\n");
                            printf(" ║               PM2.5 WEEKLY ANALYSIS                  ║\n");
                            printf(" ╠══════════════════════════════════════════════════════╣\n");                           
                            printf(" ║  Average PM2.5        :   %-27.2f║\n", avg_pm);
                            printf(" ║  Hightest PM2.5       :   %-27.2f║\n", max);// ใช้ %-27.2f เพื่อบังคับให้ตัวเลขกินพื้นที่ 27 ช่องว่างทางขวาเสมอ ขอบถึงจะตรง
                            
                            if (avg_pm <= 25) {                               
                                printf(" ║  Status               :   EXCELLENT (Blue)           ║\n");// EXCELLENT (Blue) = 16 ตัวอักษร -> เติม Space 11 ตัว
                                printf(" ╠══════════════════════════════════════════════════════╣\n");
                                printf(" ║  [ Health Review ]                                   ║\n");
                                printf(" ║  Your lungs had a great week! Air quality was        ║\n");
                                printf(" ║  very good. Perfect for outdoor activities.          ║\n");
                            } 
                            else if (avg_pm <= 50) {
                               
                                printf(" ║  Status               :   GOOD (Green)               ║\n");// GOOD (Green) = 12 ตัวอักษร -> เติม Space 15 ตัว
                                printf(" ╠══════════════════════════════════════════════════════╣\n");
                                printf(" ║  [ Health Review ]                                   ║\n");
                                printf(" ║  Air quality was decent. You can do outdoor          ║\n");
                                printf(" ║  activities normally.                                ║\n");
                            } 
                            else if (avg_pm <= 100) {
                               
                                printf(" ║  Status               :   MODERATE (Yellow)          ║\n");// MODERATE (Yellow) = 17 ตัวอักษร -> เติม Space 10 ตัว
                                printf(" ╠══════════════════════════════════════════════════════╣\n");
                                printf(" ║  [ Health Review ]                                   ║\n");
                                printf(" ║  Some pollution detected. Reduce heavy cardio        ║\n");
                                printf(" ║  outdoors if you have respiratory issues.            ║\n");
                            } 
                            else if (avg_pm <= 200) {                                
                                printf(" ║  Status               :   UNHEALTHY (Orange)         ║\n");// UNHEALTHY (Orange) = 18 ตัวอักษร -> เติม Space 9 ตัว
                                printf(" ╠══════════════════════════════════════════════════════╣\n");
                                printf(" ║  [ Health Review ]                                   ║\n");
                                printf(" ║  High pollution week. You might feel irritation.     ║\n");
                                printf(" ║  Please wear a mask and avoid outdoor exercise.      ║\n");
                            } 
                            else {
                               
                                printf(" ║  Status               :   HAZARDOUS (Red)            ║\n");// HAZARDOUS (Red) = 15 ตัวอักษร -> เติม Space 12 ตัว
                                printf(" ╠══════════════════════════════════════════════════════╣\n");
                                printf(" ║  [ Health Review ]                                   ║\n");
                                printf(" ║  CRITICAL EXPOSURE! Dangerous levels detected.       ║\n");
                                printf(" ║  Check your health if you feel unwell. Stay inside.  ║\n");
                            }

                            printf(" ╚══════════════════════════════════════════════════════╝\n");
                            
                            printf("=====================================================\n");
                            printf("Returning to main menu...\n");
                            printf("=====================================================\n");
                            break;

                case 0:
                            printf("Thank you for usinng Super Program \n");
                            printf("GRADE A \n");
                            return 0;
                default:
                            printf("Invalid number\n");
                            break;
                    }
                }
            return 0;
        }


/*
 * ======================================================================================
 * [ เอกสารอ้างอิงและที่มาของข้อมูล (References) ]
 * ======================================================================================
 * * 1. ข้อมูลการปล่อยก๊าซเรือนกระจกของอาหาร (Emission Factors):
 * อ้างอิงจาก: "Our World in Data: Environmental Impacts of Food Production"
 * (อิงงานวิจัยของ Poore & Nemecek, 2018)
 * - เนื้อสัตว์ (Meat): ปล่อยก๊าซ ~30-60 kgCO2e/kg (ในโปรแกรมใช้ค่า 30 เพื่อไม่ให้สูงเกินไป)
 * - ข้าว (Rice): ~4.5 kgCO2e/kg (สูงกว่าพืชอื่นเนื่องจากก๊าซมีเทนจากการทำนาแบบขังน้ำ)
 * - ผัก/ผลไม้: ~1.0 kgCO2e/kg
 *
 * 2. การเปรียบเทียบผลกระทบ (Impact Equivalencies):
 * อ้างอิงจาก: "US EPA Greenhouse Gas Equivalencies Calculator"
 * เว็บไซต์: https://www.epa.gov/energy/greenhouse-gas-equivalencies-calculator
 * - ขยะอาหาร 1 kgCO2e เทียบเท่ากับการชาร์จมือถือได้ประมาณ 122 รอบ
 * ======================================================================================
 */