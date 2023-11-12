#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE_TITLE 100
#define MAX_SIZE_DESCRIPTION 200
#define MAX_SIZE_TIME 33

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


int main() {
    char testCases[][100] = {
        "Add [title] [description] [time]",    // valid
        "Add [title] [description [time]" ,   // invalid
        "Add [title] [description] [time"  ,  // invalid
        "Add [[] [] []] [description] time" ,   // invalid
        "Add [[] [] []] [description] [time]"  ,  // valid
        "Add [[] [] []] [description [time]"  ,  // invalid
        "Add [[] [] []] [description] [time"  ,  // invalid
        "Add [[] [] []] [description] time]"   , // invalid
        "Add [[] []] [[]] [time]"    ,// valid
        "Add [[title] [description] [time]]"   // valid
    };

    for (int i = 0; i < 9; ++i) {
        char title[MAX_SIZE_TITLE];
        char description[MAX_SIZE_DESCRIPTION];
        char time[MAX_SIZE_TIME];

        getTitleFromAdd(testCases[i], title);
        getDescriptionFromAdd(testCases[i], description);
        getTimeFromAdd(testCases[i], time);

        printf("\nTest Case %d:\n", i + 1);
        if (title != NULL)
            printf("Title: %s\n", title);
        if (description != NULL)
            printf("Description: %s\n", description);
        if (time != NULL)
            printf("Time: %s\n", time);
    }

    return 0;
}



