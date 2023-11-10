#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_HOUR 23
#define MAX_MINUTE 59
#define MAX_DAY 31
#define MAX_MONTH 12
#define MAX_YEAR 9999
#define MIN_HOUR 0
#define MIN_MINUTE 0
#define MIN_DAY 1
#define MIN_MONTH 1
#define MIN_YEAR 1
#define PREFIX_WRONG_HOUR_DATETIME1 1100
#define PREFIX_WRONG_MINUTE_DATETIME1 2100
#define PREFIX_WRONG_DAY_DATETIME1 3100
#define PREFIX_WRONG_MONTH_DATETIME1 4100
#define PREFIX_WRONG_YEAR_DATETIME1 510000
#define PREFIX_WRONG_HOUR_DATETIME2 1200
#define PREFIX_WRONG_MINUTE_DATETIME2 2200
#define PREFIX_WRONG_DAY_DATETIME2 3200
#define PREFIX_WRONG_MONTH_DATETIME2 4200
#define PREFIX_WRONG_YEAR_DATETIME2 520000

// Function to check if a component (for int type) of time is valid
int isValidComponent_INT(int component, int maxValue, int minValue, int prefixReturnValue) {
    if (component < minValue || component > maxValue) {
        return prefixReturnValue + component; // Component is invalid
    }

    return 1; // Component is valid
}

// Function to check if a component (for char type) of time is valid
int isValidComponent_CHAR(char *component, int maxValue, int minValue, int prefixReturnValue, int* outValue) {
    // Have not handle the case component is NULL
    // or have the length which not match the form
    // or cannot turn into int
    // Example: 1 for hh, 100 for hh, 23 for yyyy, 1231231 for yyyy, ab for hh

    // Turn string to int
    *outValue = atoi(component);
    return isValidComponent_INT(*outValue, maxValue, minValue, prefixReturnValue);
}


// Function to check if the year is a leap year
int isLeapYear(int year) {
    if (year % 400 == 0) return 1;
	if (year % 100 == 0) return 0;
	if (year % 4 == 0) return 1;
	return 0;
}

// Function to get the number of days in a specific month
int daysInMonth(int month, int year) {
    if (month > 12 || month < 1) return -1;
    const int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year)) return 29;

    return daysPerMonth[month];
}

// Function to check if the time is valid
int checkTime(char *raw_time) {

    int checker, hour1, minute1, year1, month1, day1, hour2, minute2, year2, month2, day2;

    // Extract and check if datetime1 is valid
    checker = isValidComponent_CHAR(strtok(raw_time, ":"), MAX_HOUR, MIN_HOUR, PREFIX_WRONG_HOUR_DATETIME1, &hour1);
    if (checker != 1 || hour1 < 0) return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "|"), MAX_MINUTE, MIN_MINUTE, PREFIX_WRONG_MINUTE_DATETIME1, &minute1);
    if (checker != 1 || minute1 < 0) return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "/"), MAX_DAY, MIN_DAY, PREFIX_WRONG_DAY_DATETIME1, &day1);
    if (checker != 1 || day1 < 0) return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "/"), MAX_MONTH, MIN_MONTH, PREFIX_WRONG_MONTH_DATETIME1, &month1);
    if (checker != 1 || month1 < 0) return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "-"), MAX_YEAR, MIN_YEAR, PREFIX_WRONG_YEAR_DATETIME1, &year1);
    if (checker != 1 || year1 < 0) return checker;

    // Check day again after extract month and year, don't strtok() again
    checker = isValidComponent_INT(day1, daysInMonth(month1, year1), MIN_DAY, PREFIX_WRONG_DAY_DATETIME1);
    if (checker != 1) return checker;



    // Extract and check if datetime2 is valid
    checker = isValidComponent_CHAR(strtok(NULL, ":"), MAX_HOUR, MIN_HOUR, PREFIX_WRONG_HOUR_DATETIME2, &hour2);
    if (checker != 1 || hour2 < 0) return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "|"), MAX_MINUTE, MIN_MINUTE, PREFIX_WRONG_MINUTE_DATETIME2, &minute2);
    if (checker != 1 || minute2 < 0) return checker;
    
    checker = isValidComponent_CHAR(strtok(NULL, "/"), MAX_DAY, MIN_DAY, PREFIX_WRONG_DAY_DATETIME2, &day2);
    if (checker != 1 || day2 < 0) return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "/"), MAX_MONTH, MIN_MONTH, PREFIX_WRONG_MONTH_DATETIME2, &month2);
    if (checker != 1 || month2 < 0) return checker;
        
    checker = isValidComponent_CHAR(strtok(NULL, "\0"), MAX_YEAR, MIN_YEAR, PREFIX_WRONG_YEAR_DATETIME2, &year2);
    if (checker != 1 || year2 < 0) return checker;

    // Check day again after extract month and year, don't strtok() again
    checker = isValidComponent_INT(day2, daysInMonth(month2, year2), MIN_DAY, PREFIX_WRONG_DAY_DATETIME2);
    if (checker != 1) return checker;


    // Check if datetime2 is not earlier than datetime1
    if (year1 > year2) return 0;
    if (year1 == year2)
    {
        if (month1 > month2) return 0;
        if (month1 == month2)
        {
            if (day1 > day2) return 0;
            if (day1 == day2)
            {
                if (hour1 > hour2) return 0;
                if (hour1 == hour2)
                    if (minute1 > minute2) return 0;
            }
        }
    }

    // The time is valid
    return -1;
}

int main() {
    // Test cases
    char validTime[] = "12:30|15/11/2023-16:45|15/11/2023";
    char invalid_but_result_is_minus1[] = "-1101:30|15/11/2023-16:45|15/11/2023";
    char invalid_hour1[] = "25:30|15/11/2023-16:45|15/11/2023";
    char invalid_mimute2[] = "12:30|15/11/2023-16:75|15/11/2023";
    char invalid_day1[] = "12:30|32/11/2023-16:45|15/11/2023";
    char invalid_month1[] = "12:30|15/13/2023-16:45|15/11/2023";
    char invalid_year1[] = "12:30|15/11/0000-16:45|15/11/2023";
    char invalidCondition3[] = "12:30|15/11/2023-11:45|15/11/2023";
    char invalid_both[] = "12:30|32/11/2023-16:45|15/11/0000";
    char invalid_not_digit_but_result_is_minus1[] = "ab:30|15/11/2023-16:45|15/11/2023"; //atoi("ab") is 0


    // Test the checkTime function
    printf("validTime: %d\n", checkTime(validTime));
    printf("invalid_but_result_is_minus1: %d\n", checkTime(invalid_but_result_is_minus1));
    printf("invalid_hour1: %d\n", checkTime(invalid_hour1));
    printf("invalid_mimute2: %d\n", checkTime(invalid_mimute2));
    printf("invalid_day1: %d\n", checkTime(invalid_day1));
    printf("invalid_month1: %d\n", checkTime(invalid_month1));
    printf("invalid_year1: %d\n", checkTime(invalid_year1));
    printf("invalidCondition3: %d\n", checkTime(invalidCondition3));
    printf("invalid_both: %d\n", checkTime(invalid_both));
    printf("invalid_not_digit_but_result_is_minus1: %d\n", checkTime(invalid_not_digit_but_result_is_minus1));


    return 0;
}
