#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>



// CONSTANTS
#define MAX_NO_TASKS 99
#define MAX_SIZE_TITLE 100
#define MAX_SIZE_DESCRIPTION 200
#define MAX_SIZE_TIME 33
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

// Enum to represent command types
typedef enum {
    ADD,
    EDIT,
    SHOW,
    DELETE,
    QUIT,
    INVALID
} CommandType;

// Enum to represent task statuses
typedef enum
{
    IN_PROGRESS,
    DONE,
    ARCHIVED,
    INVALID_STATUS
} Status;

// Global variable for status strings
const char *statusStrings[] = {"In Progress", "Done", "Archived", "Invalid Status"};



// STRING FUNCTIONS
// Function to extract information between square brackets
void extractBetweenBrackets(char *start, char *end, char *output, size_t outputSize) {
    if (start != NULL && end != NULL) {
        // Calculate the length of the content between square brackets
        size_t length = end - start - 1;
        
        // Ensure that the length doesn't exceed the output buffer size
        if (length >= outputSize) {
            length = outputSize - 1;
        }

        // Copy the content to the output variable
        strncpy(output, start + 1, length);
        // Null-terminate the extracted content
        output[length] = '\0';
    }
}

// Function to safely copy strings
void safeStringCopy(char *dest, const char *src, size_t destSize) {
    if (dest != NULL && src != NULL && destSize > 0) {
        strncpy(dest, src, destSize - 1);  // Leave space for the null terminator
        dest[destSize - 1] = '\0';  // Ensure null-terminated
    }
}




// STRUCT TASK AND ITS COPY FUNCTION
// Structure to represent a task
struct Task
{
    int num;
    char title[MAX_SIZE_TITLE];
    char description[MAX_SIZE_DESCRIPTION];
    char time[MAX_SIZE_TIME];
    Status status;
};

// Function to copy a task
void copyTask(struct Task *dest, const struct Task *src)
{
    // dest->num = src->num;  // no need and should not to copy num
    safeStringCopy(dest->title, src->title, sizeof(dest->title));
    safeStringCopy(dest->description, src->description, sizeof(dest->description));
    dest->status = src->status;
}





// REQUIREMENT 1
// Function to get the command type
CommandType getCommandType(char *command) {
    // Assuming the maximum length of the first word is 10
    char firstWord[10];



    // Extract the first word from the command
    // int i = 0;
    // while (command[i] != '\0' && command[i] != ' ' && i < 10) {
    //     firstWord[i] = command[i];
    //     i++;
    // }
    // firstWord[i] = '\0';

    // You can use this below line instead above code 
    // if you want " Quit" is QUIT instead of INVALID
    sscanf(command, "%s", firstWord);



    // Compare the first word with command types
    if (strcmp(firstWord, "Add") == 0)
        return ADD;
    if (strcmp(firstWord, "Edit") == 0)
        return EDIT;
    if (strcmp(firstWord, "Show") == 0)
        return SHOW;
    if (strcmp(firstWord, "Delete") == 0)
        return DELETE;
    if (strcmp(firstWord, "Quit") == 0)
        return QUIT;
    // Default case for invalid commands
    return INVALID;
}



// REQUIREMENT 2
// Function to extract title from Add command
void getTitleFromAdd(char *command, char *out_title)
{
    // FIND FIRST BRACKET FOR <TITLE>
    // Find opening bracket
    char *start = strchr(command, '[');
    // Let out_title NULL if can't find opening bracket
    if (start == NULL)
    {
        out_title[0] = '\0';
        return;
    }
    // Find closing bracket
    char *end = strchr(start, ']');
    // Let out_title NULL if can't find closing bracket
    if (end == NULL)
    {
        out_title[0] = '\0';
        return;
    }

    extractBetweenBrackets(start, end, out_title, MAX_SIZE_TITLE);
}

// Function to extract description from Add command
void getDescriptionFromAdd(char *command, char *out_description)
{
    // FIND FIRST BRACKET FOR <TITLE> TO SKIP IT
    // Find opening bracket
    char *start = strchr(command, '[');
    // Let out_description NULL if can't find opening bracket
    if (start == NULL)
    {
        out_description[0] = '\0';
        return;
    }
    // Find closing bracket
    char *end = strchr(start, ']');
    // Let out_description NULL if can't find closing bracket
    if (end == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    // FIND SECOND BRACKET FOR <DESCRIPTION>
    // Find opening bracket
    start = strchr(end, '[');
    // Let out_description NULL if can't find opening bracket
    if (start == NULL)
    {
        out_description[0] = '\0';
        return;
    }
    // Find closing bracket
    end = strchr(start, ']');
    // Let out_description NULL if can't find closing bracket
    if (end == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    extractBetweenBrackets(start, end, out_description, MAX_SIZE_DESCRIPTION);
}

// Function to extract time from Add command
void getTimeFromAdd(char *command, char *out_time)
{
    // FIND FIRST BRACKET FOR <TITLE> TO SKIP IT
    // Find opening bracket
    char *start = strchr(command, '[');
    // Let out_time NULL if can't find opening bracket
    if (start == NULL)
    {
        out_time[0] = '\0';
        return;
    }
    // Find closing bracket
    char *end = strchr(start, ']');
    // Let out_time NULL if can't find closing bracket
    if (end == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // FIND SECOND BRACKET FOR <DESCRIPTION> TO SKIP IT
    // Find opening bracket
    start = strchr(end, '[');
    // Let out_time NULL if can't find opening bracket
    if (start == NULL)
    {
        out_time[0] = '\0';
        return;
    }
    // Find closing bracket
    end = strchr(start, ']');
    // Let out_time NULL if can't find closing bracket
    if (end == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // FIND THIRD BRACKET FOR <TIME>
    // Find opening bracket
    start = strchr(end, '[');
    // Let out_time NULL if can't find opening bracket
    if (start == NULL)
    {
        out_time[0] = '\0';
        return;
    }
    // Find closing bracket
    end = strchr(start, ']');
    // Let out_time NULL if can't find closing bracket
    if (end == NULL)
    {
        out_time[0] = '\0';
        return;
    }
    extractBetweenBrackets(start, end, out_time, MAX_SIZE_TIME);
}



// REQUIREMENT 3 4
// Function to check if the title or description is valid
int checkValidtTitleAndDescription(char *raw_string, size_t max_length) {
    // Check if the string violates the maximum length condition
    size_t length = strlen(raw_string);
    if (length > max_length) {
        return (int)length;
    }

    // Check each character in the string
    for (size_t i = 0; i < length; ++i) {
        char currentChar = raw_string[i];

        // Check if the character is a valid type
        if (!(isalpha(currentChar) || isdigit(currentChar) ||
              currentChar == ' ' || currentChar == ',' ||
              currentChar == '.' || currentChar == '-' ||
              currentChar == ':' || currentChar == '|' ||
              currentChar == '/')) {
            // Return the position of the first invalid character
            return (int)i;
        }

        // Check if the string starts or ends with whitespace
        if (i == 0 && isspace(currentChar)) {
            return (int)i;
        }
        if (i == length - 1 && isspace(currentChar)) {
            return (int)i;
        }
    }

    // The string is valid
    return -1;
}

// Function to check if the title is valid
int checkTitle(char *raw_title) {
    return checkValidtTitleAndDescription(raw_title, MAX_SIZE_TITLE);
}

// Function to check if the description is valid
int checkDescription(char *raw_description) {
    return checkValidtTitleAndDescription(raw_description, MAX_SIZE_DESCRIPTION);
}



// REQUIREMENT 5
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



// REQUIREMENT 6
// Function to extract title from Edit command
void getTitleFromEdit(char *command, char *out_title) {
    // Find opening bracket
    char *start = strstr(command, "title:[");
    // Let out_title NULL if can't find opening bracket
    if (start == NULL)
    {
        out_title[0] = '\0';
        return;
    }
    // Find closing bracket
    char *end = strchr(start, ']');
    // Let out_title NULL if can't find closing bracket
    if (end == NULL)
    {
        out_title[0] = '\0';
        return;
    }

    extractBetweenBrackets(start + strlen("title:"), end, out_title, MAX_SIZE_TITLE);
}

// Function to extract description from Edit command
void getDescriptionFromEdit(char *command, char *out_description) {
    // Find opening bracket
    char *start = strstr(command, "description:[");
    // Let out_description NULL if can't find opening bracket
    if (start == NULL)
    {
        out_description[0] = '\0';
        return;
    }
    // Find closing bracket
    char *end = strchr(start, ']');
    // Let out_description NULL if can't find closing bracket
    if (end == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    extractBetweenBrackets(start + strlen("description:"), end, out_description, MAX_SIZE_DESCRIPTION);
}

// Function to extract time from Edit command
void getTimeFromEdit(char *command, char *out_time) {
    // Find opening bracket
    char *start = strstr(command, "time:[");
    // Let out_time NULL if can't find opening bracket
    if (start == NULL)
    {
        out_time[0] = '\0';
        return;
    }
    // Find closing bracket
    char *end = strchr(start, ']');
    // Let out_time NULL if can't find closing bracket
    if (end == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    extractBetweenBrackets(start + strlen("time:"), end, out_time, MAX_SIZE_TIME);
}



// REQUIREMENT 7
// Function to extract <num> from Edit command
int getNumFromCommand(char *command)
{
    // Find the '#' character in the command
    char *numStart = strchr(command, '#');

    if (numStart == NULL)
    {
        // If the command does not contain the '#' character, return -1
        return -1;
    }

    // Extract the substring starting from '#' (excluding '#')
    char numString[10]; // Assuming the maximum length of <num> is 10

    // EXPLAINING:
    // numStart + 1: numStart is memory of #, so I set + 1 to skip #
    // %9: at most 9 characters should be read (to avoid buffer overflow because of numString[10]). 
    // [^ ]: It specifies a character set to match. In this case, it says "match any character except space (' ')".
    // So, it will read characters until it encounters a space.
    // numString: This is the destination variable where the read characters will be stored.
    sscanf(numStart + 1, "%9[^ ]", numString);

    // Convert the extracted string to an integer
    int num = atoi(numString);

    // Check if the conversion was successful and the value is a positive integer
    if (num <= 0) return 0; 

    return num;
}



// REQUIREMENT 8
// Function to get the field to be changed from Edit command
int getFieldFromEdit(char *edit_cmd) {
    // Find the first whitespace in the Edit command
    char *firstSpace = strchr(edit_cmd, ' ');
    if (firstSpace == NULL) {
        // If there is no first whitespace, the command is invalid
        return 0;
    }

    // Find the second whitespace in the Edit command
    // + 1 to skip the first whitespace
    char *secondSpace = strchr(firstSpace + 1, ' ');
    if (secondSpace == NULL) {
        // If there is no second whitespace, the command is invalid
        return 0;
    }

    // Find the colon in the Edit command
    char *colon = strchr(secondSpace, ':');
    if (colon == NULL) {
        // If there is no colon, the command is invalid
        return 0;
    }

    // Extract the field to be changed
    char field[20]; // Assuming the maximum length of the field is 20

    //strcpy(source string, begin location, number of character to copy)
    strncpy(field, secondSpace + 1, colon - secondSpace - 1);

    // Null-terminate the extracted field
    field[colon - secondSpace - 1] = '\0'; 

    // Compare the extracted field with valid strings
    if (strcmp(field, "title") == 0)
        return 1;
    if (strcmp(field, "description") == 0)
        return 2;
    if (strcmp(field, "time") == 0)
        return 3;
    if (strcmp(field, "status") == 0)
        return 4;
    // If the field is invalid, return 0
    return 0;
}



// REQUIREMENT 9
// Function to display information of a Task
void printTask(struct Task *task)
{
    printf("Task #%d\n", task->num);
    printf("Title: %s\n", task->title);
    printf("Description: %s\n", task->description);
    printf("Status: %s\n", statusStrings[task->status]);
    printf("-----------\n");
}



// REQUIREMENT 10
// Function to display all tasks in the array
void printAllTasks(struct Task *array_tasks, int no_tasks)
{
    for (int i = 0; i < no_tasks; ++i)
    {
        printTask(&array_tasks[i]);
    }
}



// REQUIREMENT 11
// Print task by task number
void printTaskByNum(struct Task *array_tasks, int no_tasks, int num)
{
    if (num < 1)
    {
        printf("%d is invalid input because #num must be positive\n", num);
        return;
    }
    for (int i = 0; i < no_tasks; ++i)
    {
        if (array_tasks[i].num == num)
        {
            printTask(&array_tasks[i]);
            return; // Assuming task numbers are unique, so we can exit early
        }
    }
    printf("Task #%d not found\n", num);
}



// REQUIREMENT 12
// Print the first quan tasks
void printHeadTasks(struct Task *array_tasks, int no_tasks, int quan)
{
    int endIndex = (quan < no_tasks) ? quan : no_tasks;
    for (int i = 0; i < endIndex; ++i)
    {
        printTask(&array_tasks[i]);
    }
}



// REQUIREMENT 13
// Print the last quan tasks
void printTailTasks(struct Task *array_tasks, int no_tasks, int quan)
{
    int startIndex = (quan < no_tasks) ? no_tasks - quan : 0;
    for (int i = startIndex; i < no_tasks; ++i)
    {
        printTask(&array_tasks[i]);
    }
}



// REQUIREMENT 14
// Function to print tasks filtered by title
void printFilteredTasksByTitle(struct Task *array_tasks, int no_tasks, const char *filter_title)
{
    if (filter_title == NULL || *filter_title == '\0')
    {
        printAllTasks(array_tasks, no_tasks);
        return;
    }
    // Non-empty filter_title, search for tasks with matching titles
    for (int i = 0; i < no_tasks; ++i)
    {
        if (strstr(array_tasks[i].title, filter_title) != NULL)
        {
            printTask(&array_tasks[i]);
        }
    }
}



// REQUIREMENT 15
// Function to print tasks filtered by description
void printFilteredTasksByDescription(struct Task *array_tasks, int no_tasks, char *filter_description)
{
    if (filter_description == NULL || *filter_description == '\0')
    {
        printAllTasks(array_tasks, no_tasks);
        return;
    }
    // Non-empty filter_title, search for tasks with matching titles
    for (int i = 0; i < no_tasks; ++i)
    {
        if (strstr(array_tasks[i].description, filter_description) != NULL)
        {
            printTask(&array_tasks[i]);
        }
    }
}



// REQUIREMENT 16
// Function to print tasks filtered by status
void printFilteredTasksByStatus(struct Task *array_tasks, int no_tasks, Status filter_status)
{
    for (int i = 0; i < no_tasks; ++i)
    {
        if (array_tasks[i].status == filter_status)
        {
            printTask(&array_tasks[i]);
        }
    }
}



// REQUIREMENT 17
// Function to add a new task to the array
bool addTask(struct Task *array_tasks, int *no_tasks, char *new_title, char *new_description, char *new_time) {
    // Check if there is space for a new task
    if (*no_tasks < MAX_NO_TASKS) {
        // Set values for the new task
        array_tasks[*no_tasks].num = *no_tasks + 1;
        safeStringCopy(array_tasks[*no_tasks].title, new_title, MAX_SIZE_TITLE);
        safeStringCopy(array_tasks[*no_tasks].description, new_description, MAX_SIZE_DESCRIPTION);
        safeStringCopy(array_tasks[*no_tasks].time, new_time, MAX_SIZE_TIME);
        array_tasks[*no_tasks].status = IN_PROGRESS;

        // Increment the number of tasks
        (*no_tasks)++;

        // Return true to indicate success
        return true;
    }
    return false;
}



// REQUIREMENT 18
// Function to delete a task by num
bool deleteTask(struct Task *array_tasks, int *no_tasks, int num)
{
    // Check if the task with the given num exists
    int index = -1;
    for (int i = 0; i < *no_tasks; ++i)
    {
        if (array_tasks[i].num == num)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        // Task with the given num not found
        return false;
    }

    // Shift elements to fill the gap left by the deleted task
    for (int i = index; i < *no_tasks - 1; ++i)
    {
        copyTask(&array_tasks[i], &array_tasks[i + 1]);
        // copyTask() does not copy num, so no need to decrease the num
    }

    // Update the number of tasks
    (*no_tasks)--;

    return true;
}




// Present all requirements with tricky testcases
void requirement1() {

}

void requirement2() {
    
}

void requirement3() {
    
}

void requirement4() {
    
}

void requirement5() {
    
}

void requirement6() {

}

void requirement7() {
    
}

void requirement8() {
    
}

void requirement9() {
    
}

void requirement10() {
    
}
void requirement11() {

}

void requirement12() {
    
}

void requirement13() {
    
}

void requirement14() {
    
}

void requirement15() {
    
}
void requirement16() {

}

void requirement17() {
    
}

void requirement18() {
    
}

void showAll_requirement() {

}




// Present all 5 types of command as Interaction with a completed program
void program() {

}






int main() {


    return 0;
}





























































































































































































































































































































































































































































































































































































































































































































































































































































































































































































