/*
 * Super Program - Multi-utility Console Application
 * 
 * Features:
 *   - Food Waste Calculator
 *   - PM2.5 Air Quality Review
 *   - Tax Calculator (Personal Income & VAT)
 *   - Multi-language Support (English/Thai)
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
    #define SET_UTF8() do { SetConsoleOutputCP(65001); SetConsoleCP(65001); } while(0)
#else
    #define SLEEP_MS(ms) /* No-op on non-Windows */
    #define SET_UTF8()   /* No-op on non-Windows */
#endif

/* ============================================================
   Constants
   ============================================================ */
#define EMISSION_FACTOR_RICE      4.5f
#define EMISSION_FACTOR_MEAT      30.0f
#define EMISSION_FACTOR_VEG_FRUIT 1.0f
#define CHARGES_PER_KGCO2         121.7f
#define MAX_PM25_RECORDS          50
#define LANG_MAX                  3
#define FOOD_WASTE_COST_PER_KG    50.0f
#define FOOD_WASTE_CO2_PER_KG     2.0f
#define TREE_CO2_ABSORPTION       0.5f
#define VAT_RATE                  0.07f
#define VAT_DIVISOR               1.07f

/* Tax deduction constants */
#define TAX_DEDUCTION_PERSONAL    60000.0f
#define TAX_DEDUCTION_WORK_MAX    100000.0f
#define TAX_DEDUCTION_WORK_RATE   0.50f

/* Tax brackets */
#define TAX_BRACKET_1             150000.0f
#define TAX_BRACKET_2             300000.0f
#define TAX_BRACKET_3             500000.0f
#define TAX_BRACKET_4             750000.0f
#define TAX_BRACKET_5             1000000.0f
#define TAX_BRACKET_6             2000000.0f
#define TAX_BRACKET_7             5000000.0f

/* Tax rates */
#define TAX_RATE_1                0.0f
#define TAX_RATE_2                0.05f
#define TAX_RATE_3                0.10f
#define TAX_RATE_4                0.15f
#define TAX_RATE_5                0.20f
#define TAX_RATE_6                0.25f
#define TAX_RATE_7                0.30f
#define TAX_RATE_8                0.35f

/* Menu options */
#define MENU_EXIT                 0
#define MENU_FOOD_WASTE           1
#define MENU_PM25                 2
#define MENU_TAX                  3
#define MENU_LANGUAGE             4

/* ============================================================
   Global Variables
   ============================================================ */
static char g_current_lang[LANG_MAX] = "EN";

/* ============================================================
   Helper Functions
   ============================================================ */

/**
 * Get localized string based on current language
 * @param en_text English text
 * @param th_text Thai text
 * @return Localized string
 */
static const char* lang_str(const char *en_text, const char *th_text) {
    return (strcmp(g_current_lang, "TH") == 0) ? th_text : en_text;
}

/**
 * Set the current language
 * @param lang Language code ("EN" or "TH")
 */
static void lang_set(const char *lang) {
    if (lang == NULL || strlen(lang) == 0 || strlen(lang) >= LANG_MAX) {
        printf("[ ERROR ] Invalid language code.\n");
        return;
    }
    strncpy(g_current_lang, lang, LANG_MAX - 1);
    g_current_lang[LANG_MAX - 1] = '\0';
}

/**
 * Safe integer input with validation
 * @param prompt Prompt message
 * @param value Pointer to store the result
 * @return true if input successful, false otherwise
 */
static bool read_int(const char *prompt, int *value) {
    char buffer[64];
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }
    if (sscanf(buffer, "%d", value) != 1) {
        return false;
    }
    return true;
}

/**
 * Safe float input with validation
 * @param prompt Prompt message
 * @param value Pointer to store the result
 * @return true if input successful, false otherwise
 */
static bool read_float(const char *prompt, float *value) {
    char buffer[64];
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }
    if (sscanf(buffer, "%f", value) != 1) {
        return false;
    }
    return true;
}

/**
 * Clear input buffer
 */
static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
