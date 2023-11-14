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

const int inputStatusSize = 1;

char * input_command_name[] = {"Add", "Edit", "Show", "Delete", "Quit"};

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







enum CommandType getCommandType(char * command) {
    // "Delete" is longest so let max length firstWord is 7 then extract it
    char firstWord[7] = "";
    sscanf(command, "%9s", firstWord);


    // Compare the first word with command types
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(firstWord, input_command_name[i]) == 0)
            return i + 1; // already match with enum
    }

    // Default case for invalid commands
    return INVALID;
}

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

    // If open and close bracket is found, copy the between content
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