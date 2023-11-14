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

const int maxHour = 23;
const int minHour = 0;
const int wrongHour1 = 1100;
const int wrongHour2 = 1200;


const int maxMinute = 59;
const int minMinute = 0;
const int wrongMinute1 = 2100;
const int wrongMinute2 = 2200;


const int maxDay = 31;
const int minDay = 1;
const int wrongDay1 = 3100;
const int wrongDay2 = 3200;

const int maxMonth = 12;
const int mimMonth = 1;
const int wrongMonth1 = 4100;
const int wrongMonth2 = 4200;

const int maxYear = 9999;
const int minYear = 0;
const int wrongYear1 = 510000;
const int wrongYear2 = 520000;

char * input_command_name[] = {"Add", "Edit", "Show", "Delete", "Quit"};

char * input_field_name[] = {"title", "description", "time", "status"};


bool isSpace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isAlphabet(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char toLowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}


void copyStr(char *dest, const char *src, size_t destSize) {
    // Ensure that dest is not NULL and destSize is greater than 0
    if (dest == NULL || destSize == 0) {
        return;
    }

    size_t i;
    // loops will run until dest or sre reach its size
    // leave 1 last char of dest to be null-terminated
    for (i = 0; i < destSize - 1 && src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }

    dest[i] = '\0'; // null-terminated 1 last char
}






// Requirement 1
enum CommandType getCommandType(char * command) {
    // "Delete" is longest so let max length firstWord is 7 then extract it
    char firstWord[7] = "";
    sscanf(command, "%9s", firstWord);


    // Loop to compare with char * input_command_name[] = {"Add", "Edit", "Show", "Delete", "Quit"};
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(firstWord, input_command_name[i]) == 0)
            return i + 1; // already match with enum
    }

    // Default case for invalid commands
    return INVALID;
}

// Requirement 2
void getTitleFromAdd(char *command, char *out_title)
{
    // Find opening bracket of title
    char *open1 = strchr(command, '[');
    // Output NULL if can't find opening bracket
    if (open1 == NULL)
    {
        out_title[0] = '\0';
        return;
    }

    // Find closing bracket of title
    char *close1 = strchr(open1 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close1 == NULL)
    {
        out_title[0] = '\0';
        return;
    }

    // If open and close bracket is found, extract the between content
    size_t start = open1 - command + 1;
    size_t length = close1 - open1;
    if (length > MAX_LENGTH_TITLE) {
        length = MAX_LENGTH_TITLE + 1;
    }
    copyStr(out_title, command + start, length);
}

void getDescriptionFromAdd(char *command, char *out_description)
{
    // Find opening bracket of title
    char *open1 = strchr(command, '[');
    // Output NULL if can't find opening bracket
    if (open1 == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    // Find closing bracket of title
    char *close1 = strchr(open1 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close1 == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    // Find opening bracket of description
    char *open2 = strchr(close1 + 1, '[');
    // Output NULL if can't find opening bracket
    if (open2 == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    // Find closing bracket of description
    char *close2 = strchr(open2 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close2 == NULL)
    {
        out_description[0] = '\0';
        return;
    }
    // If open and close bracket is found, copy the between content
    size_t start = open2 - command + 1;
    size_t length = close2 - open2;
    if (length > MAX_LENGTH_DESCRIPTION) {
        length = MAX_LENGTH_DESCRIPTION + 1;
    }
    copyStr(out_description, command + start, length);
}

void getTimeFromAdd(char *command, char *out_time)
{
    // Find opening bracket of title
    char *open1 = strchr(command, '[');
    // Output NULL if can't find opening bracket
    if (open1 == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // Find closing bracket of title
    char *close1 = strchr(open1 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close1 == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // Find opening bracket of description
    char *open2 = strchr(close1 + 1, '[');
    // Output NULL if can't find opening bracket
    if (open2 == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // Find closing bracket of description
    char *close2 = strchr(open2 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close2 == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // Find opening bracket of time
    char *open3 = strchr(close2 + 1, '[');
    // Output NULL if can't find opening bracket
    if (open3 == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // Find closing bracket of time
    char *close3 = strchr(open3 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close3 == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // If open and close bracket is found, copy the between content
    size_t start = open3 - command + 1;
    size_t length = close3 - open3;
    if (length > MAX_LENGTH_TIME) {
        length = MAX_LENGTH_TIME + 1;
    }
    copyStr(out_time, command + start, length);
}

// Requirement 3 and 4
int checkValidtTitleAndDescription(char *str, size_t max_length)
{
    // Return length if it exceed the maximum length
    size_t length = strlen(str);
    if (length > max_length) return (int)length;

    char currentChar = '\0';
    // Check each character in the string
    for (size_t i = 0; i < length; ++i)
    {
        currentChar = str[i];

        // Check if the string starts or ends with whitespace, return violate location
        if (i == length - 1 && isSpace(currentChar)) return (int)i;
        if (i == 0 && isSpace(currentChar)) return (int)i;

        // Check if the character is a valid type, return first violate location
        if (!(isDigit(currentChar) || isAlphabet(currentChar) ||
              currentChar == ':' || currentChar == '|' ||
              currentChar == '.' || currentChar == '-' ||
              currentChar == ' ' || currentChar == ',' ||
              currentChar == '/')) return (int)i;
    }

    // The string is valid
    return -1;
}

int checkDescription(char *raw_description)
{
    return checkValidtTitleAndDescription(raw_description, MAX_SIZE_DESCRIPTION);
}

int checkTitle(char *raw_title)
{
    return checkValidtTitleAndDescription(raw_title, MAX_SIZE_TITLE);
}

// Requirement 5
int isValidIntComponent(int component, int maxValue, int minValue, int wrongValue)
{
    if (component < minValue) return wrongValue + component;// Component is invalid
    if (component > maxValue) return wrongValue + component;// Component is invalid
    return -1; // Component is valid
}

int isValidStringComponent_TurnToInt(char *component, int *outValue, int maxValue, int minValue, int wrongValue)
{
    // Turn string to int
    *outValue = atoi(component);
    return isValidIntComponent(*outValue, maxValue, minValue, wrongValue);
}

int isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int numberOfDaysInMonth(int month, int year) {
    switch (month) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 31;
    }
}

int checkTime(char *raw_time)
{
    char copyTime[MAX_LENGTH_TIME] = ""; 
    copyStr(copyTime, raw_time, MAX_LENGTH_TIME + 1);
    
    int isValid, hour1, minute1, year1, month1, day1, hour2, minute2, year2, month2, day2;

    // NOTICE TO USE NULL TO CONTINUE strtok() INSTEAD copyTime again
    // Extract and check if datetime1 is valid
    isValid = isValidStringComponent_TurnToInt(strtok(copyTime, ":"), &hour1, maxHour, minHour, wrongHour1);
    if (hour1 < 0 || isValid != -1) return isValid;
    
    isValid = isValidStringComponent_TurnToInt(strtok(NULL, "|"), &minute1, maxMinute, minMinute, wrongMinute1);
    if (minute1 < 0 || isValid != -1) return isValid;
    
    isValid = isValidStringComponent_TurnToInt(strtok(NULL, "/"), &day1, maxDay, minDay, wrongDay1);
    if (day1 < 0 || isValid != -1) return isValid;

    isValid = isValidStringComponent_TurnToInt(strtok(NULL, "/"), &month1, maxMonth, mimMonth, wrongMonth1);
    if (month1 < 0 || isValid != -1) return isValid;

    isValid = isValidStringComponent_TurnToInt(strtok(NULL, "-"), &year1, maxYear, minYear, wrongYear1);
    if (year1 < 0 || isValid != -1) return isValid;
    
    isValid = isValidIntComponent(day1, numberOfDaysInMonth(month1, year1), minDay, wrongDay1);
    if (isValid != 1)
        return isValid;


    // Extract and check if datetime2 is valid
    isValid = isValidStringComponent_TurnToInt(strtok(NULL, ":"), &hour1, maxHour, minHour, wrongHour2);
    if (hour2 < 0 || isValid != -1) return isValid;
    
    isValid = isValidStringComponent_TurnToInt(strtok(NULL, "|"), &minute2, maxMinute, minMinute, wrongMinute2);
    if (minute2 < 0 || isValid != -1) return isValid;
    
    isValid = isValidStringComponent_TurnToInt(strtok(NULL, "/"), &day2, maxDay, minDay, wrongDay2);
    if (day2 < 0 || isValid != -1) return isValid;

    isValid = isValidStringComponent_TurnToInt(strtok(NULL, "/"), &month2, maxMonth, mimMonth, wrongMonth2);
    if (month2 < 0 || isValid != -1) return isValid;

    isValid = isValidStringComponent_TurnToInt(strtok(NULL, '\0'), &year2, maxYear, minYear, wrongYear2);
    if (year2 < 0 || isValid != -1) return isValid;
    
    isValid = isValidIntComponent(day2, numberOfDaysInMonth(month2, year2), minDay, wrongDay2);
    if (isValid != 1)
        return isValid;


    // Check if datetime2 is not earlier than datetime1
    if (year2 < year1 || (year2 == year1 && (month2 < month1 ||
        (month2 == month1 && (day2 < day1 || (day2 == day1 && (hour2 < hour1 ||
        (hour2 == hour1 && minute2 < minute1)))))))) {
        return 0; // Invalid due to condition 3
    }

    // The time is valid
    return -1;
}

// Requirement 6
void getTitleFromEdit(char *command, char *out_title)
{
    // Find opening bracket of title
    char *open1 = strchr(command, '[');
    // Output NULL if can't find opening bracket
    if (open1 == NULL)
    {
        out_title[0] = '\0';
        return;
    }

    // Find closing bracket of title
    char *close1 = strchr(open1 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close1 == NULL)
    {
        out_title[0] = '\0';
        return;
    }

    // If open and close bracket is found, copy the between content
    size_t start = open1 - command + 1;
    size_t length = close1 - open1;
    if (length > MAX_LENGTH_TITLE) {
        length = MAX_LENGTH_TITLE + 1;
    }
    copyStr(out_title, command + start, length);
}

void getDescriptionFromEdit(char *command, char *out_description)
{
    // Find opening bracket of description
    char *open1 = strchr(command, '[');
    // Output NULL if can't find opening bracket
    if (open1 == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    // Find closing bracket of description
    char *close1 = strchr(open1 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close1 == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    // If open and close bracket is found, copy the between content
    size_t start = open1 - command + 1;
    size_t length = close1 - open1;
    if (length > MAX_LENGTH_TITLE) {
        length = MAX_LENGTH_TITLE + 1;
    }
    copyStr(out_description, command + start, length);
}

void getTimeFromEdit(char *command, char *out_time)
{
    // Find opening bracket of time
    char *open1 = strchr(command, '[');
    // Output NULL if can't find opening bracket
    if (open1 == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // Find closing bracket of time
    char *close1 = strchr(open1 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close1 == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // If open and close bracket is found, copy the between content
    size_t start = open1 - command + 1;
    size_t length = close1 - open1;
    if (length > MAX_LENGTH_TITLE) {
        length = MAX_LENGTH_TITLE + 1;
    }
    copyStr(out_time, command + start, length);
}

// Requirement 7
int getNumFromCommand(char *command)
{
    // Find the '#' character in the command
    char *open1 = strchr(command, '#');
    // Output -1 if can't find the '#' character
    if (open1 == NULL)  return -1;

    // Find the whitespace which end the <num> component
    char *close1 = strchr(open1 + 1, ' ');
    // Output NULL if can't find the whitespace which end the <num> component
    if (close1 == NULL) return -1;

    char numStr[3] = "\0"; // MAX_NO_TASKS = 100 so 3 characters
    // If open '#' and close ' ' character is found, copy the between content
    size_t length = close1 - open1;
    size_t start = open1 - command + 1;
    if (length == 0 || length > 3) return -1;

    copyStr(numStr, command + start, length + 1);

    // Convert the extracted string to an integer
    int numInt = atoi(numStr);

    // Check if the conversion was successful and the value is a positive integer
    if (numInt <= 0)
        return 0;

    return numInt;
}

// Requirement 8
int getFieldFromEdit(char *edit_cmd)
{
    // Find the first whitespace
    char *whiteSpace = strchr(edit_cmd, ' ');
    if (whiteSpace == NULL) return 0; // The command is invalid if there is no first whitespace

    // Find the second whitespace, YOU MUST + 1 to skip the first whitespace
    whiteSpace = strchr(whiteSpace + 1, ' ');
    if (whiteSpace == NULL) return 0; // The command is invalid if there is no second whitespace

    // Find the colon in the Edit command
    char *colon = strchr(whiteSpace + 1, ':');
    if (colon == NULL) return 0; // The command is invalid if there is no colon after second whitespace

    char field[20]; // Assume the maximum length of the field is 20

    // If open and close bracket is found, copy the between content
    size_t start = whiteSpace - edit_cmd + 1;
    size_t length = colon - whiteSpace;
    if (length > 20) {
        length = 20 + 1;
    }
    copyStr(field, edit_cmd + start, length);

    // Loop to compare with char * input_field_name[] = {"title", "description", "time", "status"};
    for (int i = 0; i < 4; i++) {
        if (strcmp(field, input_field_name[i]) == 0) return i + 1;
    }

    // If the field is invalid, return 0
    return 0;
}

// Requirement 9
enum Status getStatusFromEdit(char *edit_cmd)
{
    // Find opening bracket of time
    char *open1 = strchr(edit_cmd, '[');
    // Output NULL if can't find opening bracket
    if (open1 == NULL)
    {
        edit_cmd[0] = '\0';
        return -1;
    }

    // Find closing bracket of time
    char *close1 = strchr(open1 + 1, ']');
    // Output NULL if can't find closing bracket
    if (close1 == NULL)
    {
        edit_cmd[0] = '\0';
        return -1;
    }

    // Extract the status from the Edit command
    // Only need 2 first characters to check if input has more than 1
    // And 1 more to null-terminate, so sum is 3
    char extractedInsideBracket[2] = "";

    // If open and close bracket is found, copy the between content
    size_t start = open1 - edit_cmd + 1;
    size_t length = close1 - open1;
    if (length > 2) {
        length = 2 + 1;
    }
    copyStr(extractedInsideBracket, edit_cmd + start, length);

    // Check if there's exactly 1 character extracted
    if (strlen(extractedInsideBracket) != 1) return -1;
    // Convert the status character to lowercase
    char inputStatus =  toLowercase(extractedInsideBracket[0]);

    // Return enum value based on the status character
    if (inputStatus == 'i') return IN_PROGRESS;
    if (inputStatus == 'd') return DONE;
    if (inputStatus == 'i') return ARCHIVED;
        
    return -1; // If the status character is invalid, return an invalid status
}

// Requirement 10
void printAllTasks(struct Task *array_tasks, int no_tasks)
{
    for (int i = 0; i < no_tasks; ++i) printTask(&array_tasks[i]);
}

// Requirement 11
void printTaskByNum(struct Task *array_tasks, int no_tasks, int num)
{
    if (num < 1 || num > no_tasks) return;
    for (int i = 0; i < no_tasks; ++i)
    {
        if (array_tasks[i].num == num)
        {
            printTask(&array_tasks[i]);
            return; // task numbers are unique, just exit loop here
        }
    }
}

// Requirement 12
void printHeadTasks(struct Task *array_tasks, int no_tasks, int quan)
{
    if (quan <= 0) return;
    int endLocation = (quan > no_tasks) ? no_tasks : quan;
    for (int i = 0; i < endLocation; ++i)
    {
        printTask(&array_tasks[i]);
    }
}

// Requirement 13
void printTailTasks(struct Task *array_tasks, int no_tasks, int quan)
{
    if (quan <= 0) return;
    int startLocation = (quan > no_tasks) ? 0 : no_tasks - quan;
    for (int i = startLocation; i < no_tasks; ++i)
    {
        printTask(&array_tasks[i]);
    }
}

// Requirement 14
void printFilteredTasksByTitle(struct Task *array_tasks, int no_tasks, char *filter_title)
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
    char cmd[300] = "[A very long title exceeding the maximum (100char) lengthhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhend] [des1] [time1]";
    char x[MAX_LENGTH_TITLE] = "";
    getTitleFromAdd(cmd, x);
    printf("%s", x);
    return 0;
}