#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH_COMMAND 300

#define MAX_NO_TASKS 100

#define MAX_LENGTH_TITLE 100
#define MAX_LENGTH_DESCRIPTION 200
#define MAX_LENGTH_TIME 33

#define WEEK_CELL_FIRST_COL_WIDTH 10
#define WEEK_CELL_OTHER_COL_WIDTH 20

enum Status {IN_PROGRESS, DONE, ARCHIVED};
char * status_name[] = {"In Progress", "Done", "Archived"};
enum CommandType {ADD, EDIT, SHOW, DELETE, QUIT, INVALID};
char * command_name[] = {"ADD", "EDIT", "SHOW", "DELETE", "QUIT", "INVALID"};

struct Task {
    int num;
    char title[MAX_LENGTH_TITLE+1];
    char description[MAX_LENGTH_DESCRIPTION+1];
    char time[MAX_LENGTH_TIME+1];
    enum Status status;
};

void printTask(struct Task * task) {
    printf("--------------------------------------------\n");
    printf("Num: #%d. Title: %s\n", task->num, task->title);
    printf("Description: %s\n", task->description);
    printf("Status: %s\n", status_name[task->status]);
    printf("--------------------------------------------\n");
}

void printUnsupportedTime(struct Task * task) {
    printf("----- Show week view -----\n");
    printf("Error: Unsupported time with non-zero minutes: %s\n", task->time);
    printf("In Task:\n");
    printTask(task);
}

// ------ Begin: Student Answer ------

// ------ Begin: Student Answer ------

// ============================================
// CONSTANTS
#define MAX_NO_TASKS 100
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
#define FIXED_SIZE_STATUS 1

// enum Status {IN_PROGRESS, DONE, ARCHIVED, INVALID_STATUS};

const char *statusStrings[] = {"In Progress", "Done", "Archived", "Invalid Status"};


// STRING AND CHAR FUNCTIONS
// Function to extract information between square brackets
void extractBetweenBrackets(char *start, char *end, char *output, size_t outputSize)
{
    if (start != NULL && end != NULL)
    {
        // Calculate the length of the content between square brackets
        size_t length = end - start - 1;

        // Ensure that the length doesn't exceed the output buffer size
        if (length >= outputSize)
        {
            length = outputSize - 1;
        }

        // Copy the content to the output variable
        strncpy(output, start + 1, length);
        // Null-terminate the extracted content
        output[length] = '\0';
    }
}

// Function to safely copy strings
void safeStringCopy(char *dest, const char *src, size_t destSize)
{
    if (dest != NULL && src != NULL && destSize > 0)
    {
        strncpy(dest, src, destSize - 1); // Leave space for the null terminator
        dest[destSize - 1] = '\0';        // Ensure null-terminated
    }
}

// Simplified version of tolower
char custom_tolower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// Simplified version of isspace
bool custom_isspace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

// Simplified version of isdigit
bool custom_isdigit(char c) {
    return c >= '0' && c <= '9';
}

// Simplified version of isalpha
bool custom_isalpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}


// ============================================
// REQUIREMENT 1
// Function to get the command type
enum CommandType getCommandType(char *command)
{
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

// ============================================
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

    extractBetweenBrackets(start, end, out_title, MAX_SIZE_TITLE + 1);
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

    extractBetweenBrackets(start, end, out_description, MAX_SIZE_DESCRIPTION + 1);
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
    extractBetweenBrackets(start, end, out_time, MAX_SIZE_TIME + 1);
}

// ============================================
// Function to check if the title or description is valid
int checkValidtTitleAndDescription(char *raw_string, size_t max_length)
{
    // Check if the string violates the maximum length condition
    size_t length = strlen(raw_string);
    if (length > max_length)
    {
        return (int)length;
    }

    // Check each character in the string
    for (size_t i = 0; i < length; ++i)
    {
        char currentChar = raw_string[i];

        // Check if the character is a valid type
        if (!(custom_isalpha(currentChar) || custom_isdigit(currentChar) ||
              currentChar == ' ' || currentChar == ',' ||
              currentChar == '.' || currentChar == '-' ||
              currentChar == ':' || currentChar == '|' ||
              currentChar == '/'))
        {
            // Return the position of the first invalid character
            return (int)i;
        }

        // Check if the string starts or ends with whitespace
        if (i == 0 && custom_isspace(currentChar))
        {
            return (int)i;
        }
        if (i == length - 1 && custom_isspace(currentChar))
        {
            return (int)i;
        }
    }

    // The string is valid
    return -1;
}

// REQUIREMENT 3
// Function to check if the title is valid
int checkTitle(char *raw_title)
{
    return checkValidtTitleAndDescription(raw_title, MAX_SIZE_TITLE);
}

// REQUIREMENT 4
// Function to check if the description is valid
int checkDescription(char *raw_description)
{
    return checkValidtTitleAndDescription(raw_description, MAX_SIZE_DESCRIPTION);
}

// ============================================
// REQUIREMENT 5
// Function to check if a component (for int type) of time is valid
int isValidComponent_INT(int component, int maxValue, int minValue, int prefixReturnValue)
{
    if (component < minValue || component > maxValue)
    {
        return prefixReturnValue + component; // Component is invalid
    }

    return 1; // Component is valid
}

// Function to check if a component (for char type) of time is valid
int isValidComponent_CHAR(char *component, int maxValue, int minValue, int prefixReturnValue, int *outValue)
{
    // Have not handle the case component is NULL
    // or have the length which not match the form
    // or cannot turn into int
    // Example: 1 for hh, 100 for hh, 23 for yyyy, 1231231 for yyyy, ab for hh

    // Turn string to int
    *outValue = atoi(component);
    return isValidComponent_INT(*outValue, maxValue, minValue, prefixReturnValue);
}

// Function to check if the year is a leap year
int isLeapYear(int year)
{
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}

// Function to get the number of days in a specific month
int daysInMonth(int month, int year)
{
    if (month > 12 || month < 1)
        return -1;
    const int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year))
        return 29;

    return daysPerMonth[month];
}

// Function to check if the time is valid
int checkTime(char *raw_time)
{  
    // strtok() will change the raw_time string, so you must clone it
    char clone[MAX_LENGTH_TIME] = "\0";
    safeStringCopy(clone, raw_time, MAX_LENGTH_TIME + 1);
    int checker, hour1, minute1, year1, month1, day1, hour2, minute2, year2, month2, day2;
    char copyTime[MAX_LENGTH_TIME] = ""; 
    safeStringCopy(copyTime, raw_time, MAX_LENGTH_TIME + 1);
    // Extract and check if datetime1 is valid
    checker = isValidComponent_CHAR(strtok(copyTime, ":"), MAX_HOUR, MIN_HOUR, PREFIX_WRONG_HOUR_DATETIME1, &hour1);
    if (checker != 1 || hour1 < 0)
        return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "|"), MAX_MINUTE, MIN_MINUTE, PREFIX_WRONG_MINUTE_DATETIME1, &minute1);
    if (checker != 1 || minute1 < 0)
        return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "/"), MAX_DAY, MIN_DAY, PREFIX_WRONG_DAY_DATETIME1, &day1);
    if (checker != 1 || day1 < 0)
        return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "/"), MAX_MONTH, MIN_MONTH, PREFIX_WRONG_MONTH_DATETIME1, &month1);
    if (checker != 1 || month1 < 0)
        return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "-"), MAX_YEAR, MIN_YEAR, PREFIX_WRONG_YEAR_DATETIME1, &year1);
    if (checker != 1 || year1 < 0)
        return checker;

    // Check day again after extract month and year, don't strtok() again
    checker = isValidComponent_INT(day1, daysInMonth(month1, year1), MIN_DAY, PREFIX_WRONG_DAY_DATETIME1);
    if (checker != 1)
        return checker;

    // Extract and check if datetime2 is valid
    checker = isValidComponent_CHAR(strtok(NULL, ":"), MAX_HOUR, MIN_HOUR, PREFIX_WRONG_HOUR_DATETIME2, &hour2);
    if (checker != 1 || hour2 < 0)
        return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "|"), MAX_MINUTE, MIN_MINUTE, PREFIX_WRONG_MINUTE_DATETIME2, &minute2);
    if (checker != 1 || minute2 < 0)
        return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "/"), MAX_DAY, MIN_DAY, PREFIX_WRONG_DAY_DATETIME2, &day2);
    if (checker != 1 || day2 < 0)
        return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "/"), MAX_MONTH, MIN_MONTH, PREFIX_WRONG_MONTH_DATETIME2, &month2);
    if (checker != 1 || month2 < 0)
        return checker;

    checker = isValidComponent_CHAR(strtok(NULL, "\0"), MAX_YEAR, MIN_YEAR, PREFIX_WRONG_YEAR_DATETIME2, &year2);
    if (checker != 1 || year2 < 0)
        return checker;

    // Check day again after extract month and year, don't strtok() again
    checker = isValidComponent_INT(day2, daysInMonth(month2, year2), MIN_DAY, PREFIX_WRONG_DAY_DATETIME2);
    if (checker != 1)
        return checker;

    // Check if datetime2 is not earlier than datetime1
    if (year1 > year2)
        return 0;
    if (year1 == year2)
    {
        if (month1 > month2)
            return 0;
        if (month1 == month2)
        {
            if (day1 > day2)
                return 0;
            if (day1 == day2)
            {
                if (hour1 > hour2)
                    return 0;
                if (hour1 == hour2)
                    if (minute1 > minute2)
                        return 0;
            }
        }
    }

    // The time is valid
    return -1;
}

// ============================================
// REQUIREMENT 6
// Function to extract title from Edit command
void getTitleFromEdit(char *command, char *out_title)
{
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

    extractBetweenBrackets(start + strlen("title:"), end, out_title, MAX_SIZE_TITLE + 1);
}

// Function to extract description from Edit command
void getDescriptionFromEdit(char *command, char *out_description)
{
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

    extractBetweenBrackets(start + strlen("description:"), end, out_description, MAX_SIZE_DESCRIPTION + 1);
}

// Function to extract time from Edit command
void getTimeFromEdit(char *command, char *out_time)
{
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

    extractBetweenBrackets(start + strlen("time:"), end, out_time, MAX_SIZE_TIME + 1);
}

// ============================================
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
    if (num <= 0)
        return 0;

    return num;
}

// ============================================
// REQUIREMENT 8
// Function to get the field to be changed from Edit command
int getFieldFromEdit(char *edit_cmd)
{
    // Find the first whitespace in the Edit command
    char *firstSpace = strchr(edit_cmd, ' ');
    if (firstSpace == NULL)
    {
        // If there is no first whitespace, the command is invalid
        return 0;
    }

    // Find the second whitespace in the Edit command
    // + 1 to skip the first whitespace
    char *secondSpace = strchr(firstSpace + 1, ' ');
    if (secondSpace == NULL)
    {
        // If there is no second whitespace, the command is invalid
        return 0;
    }

    // Find the colon in the Edit command
    char *colon = strchr(secondSpace, ':');
    if (colon == NULL)
    {
        // If there is no colon, the command is invalid
        return 0;
    }

    // Extract the field to be changed
    char field[20]; // Assuming the maximum length of the field is 20

    extractBetweenBrackets(secondSpace, colon, field, 21);
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

// ============================================
// REQUIREMENT 9
// Function to get the status from Edit command
enum Status getStatusFromEdit(char *edit_cmd)
{
    // Find the valid opening bracket in the Edit command
    char *start = strstr(edit_cmd, "status:[");
    // If there is no valid opening bracket, return an invalid status
    if (start == NULL)
        return -1;
    // Find closing bracket
    char *end = strchr(start, ']');
    // If there is no valid opening bracket, return an invalid status
    if (end == NULL)
        return -1;
    // Extract the status from the Edit command, only need 2 first characters if it's have more than 1, and 1 more to null-terminate, so sum is 3
    char extractedInsideBracket[3] = "";
    extractBetweenBrackets(start + strlen("status:"), end, extractedInsideBracket, 3);
    // Check if there's exactly 1 character extracted
    if (strlen(extractedInsideBracket) != FIXED_SIZE_STATUS)
        return -1;
    // Convert the status character to lowercase for case-insensitive comparison
    char status = extractedInsideBracket[0];
    status = custom_tolower(status);
    // Determine the enum Status value based on the status character
    switch (status)
    {
    case 'i':
        return IN_PROGRESS;
    case 'd':
        return DONE;
    case 'a':
        return ARCHIVED;
    default:
        // If the status character is invalid, return an invalid status
        return -1;
    }
}

// ============================================
// REQUIREMENT 10
// Function to display all tasks in the array
void printAllTasks(struct Task *array_tasks, int no_tasks)
{
    for (int i = 0; i < no_tasks; ++i)
    {
        printTask(&array_tasks[i]);
    }
}

// ============================================
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

// ============================================
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

// ============================================
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

// ============================================
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

// ============================================
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

// ============================================
// REQUIREMENT 16
// Function to print tasks filtered by status
void printFilteredTasksByStatus(struct Task *array_tasks, int no_tasks, enum Status filter_status)
{
    for (int i = 0; i < no_tasks; ++i)
    {
        if (array_tasks[i].status == filter_status)
        {
            printTask(&array_tasks[i]);
        }
    }
}

// ============================================
// REQUIREMENT 17
// Function to copy a task
void copyTask(struct Task *dest, const struct Task *src)
{
    // dest->num = src->num;  // no need and should not to copy num
    safeStringCopy(dest->title, src->title, sizeof(dest->title));
    safeStringCopy(dest->description, src->description, sizeof(dest->description));
    dest->status = src->status;
}
// // Function to add a new task to the array
bool addTask(struct Task **array_tasks, int no_tasks, char *new_title, char *new_description, char *new_time) {}
// {
//     size_t arraySize = sizeof(array_tasks) / sizeof(array_tasks[0]);
//     if (arraySize < MAX_NO_TASKS)
//     {
//         // Reallocate the array with size of MAX_NO_TASKS
//         struct Task *new_array = (struct Task *)malloc(MAX_NO_TASKS * sizeof(struct Task));
//         for (int i = 0; i < no_tasks; i++)
//         {
//             addTask(new_array, i, *array_tasks[i]->title, *array_tasks[i]->description, *array_tasks[i]->time);
//         }
//         *array_tasks = new_array;
//         return addTask(*array_tasks, no_tasks, new_title, new_description, new_time);
//     }

//     // Check if there is space for a new task
//     if (no_tasks > MAX_NO_TASKS)
//         return false;

//     // Set values for the new task
//     (array_tasks[no_tasks])->num = no_tasks + 1;
//     safeStringCopy(array_tasks[no_tasks]->title, new_title, MAX_SIZE_TITLE);
//     safeStringCopy(array_tasks[no_tasks]->description, new_description, MAX_SIZE_DESCRIPTION);
//     safeStringCopy(array_tasks[no_tasks]->time, new_time, MAX_SIZE_TIME);
//     (array_tasks[no_tasks])->status = IN_PROGRESS;
//     return true;
    
// }

// // ============================================
// // REQUIREMENT 18


// // Function to delete a task by num
bool deleteTask(struct Task *array_tasks, int no_tasks, int num)
{
    // Check if the task with the given num exists
    int index = -1;
    for (int i = 0; i < no_tasks; ++i)
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
    for (int i = index; i < no_tasks - 1; ++i)
    {
        copyTask(&array_tasks[i], &array_tasks[i + 1]);
        // copyTask() does not copy num, so no need to decrease the num
    }

    // Update the number of tasks

    return true;
}


// Other functions

// ------ End: Student Answer ------


// Other functions

// ------ End: Student Answer ------

void runTodoApp() {
    // Example of command Add
    char command[MAX_LENGTH_COMMAND+1];
    
    while (true) {
        // Sample input:
        // Add [Course Intro to Programming] [Room 701-H6] [07:00|01/10/2023-12:00|01/10/2023]
        fgets(command, MAX_LENGTH_COMMAND+1, stdin);
        command[strlen(command)-1] = '\0';

        enum CommandType commandType = getCommandType(command);
        printf("Command     : %s\n", command);
        printf("Command type: %s\n", command_name[commandType]);

        break;  // only one loop for simple test
                // actual app will break when encounter QUIT command
    }
}

int main() {
    runTodoApp();
    return 0;
}
