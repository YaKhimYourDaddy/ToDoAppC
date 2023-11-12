#include <stdio.h>
#include <string.h>
#define MAX_SIZE_TITLE 100
#define MAX_SIZE_DESCRIPTION 100
#define MAX_SIZE_TIME 100


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

int main() {
    // Test cases
    // char editCommand1[] = "Edit #1 title:[Valid Task Title]";
    // char editCommand2[] = "Edit #2 description:[Valid Task Description]";
    // char editCommand3[] = "Edit #3 time:[Valid Task Time]";

    // char editCommand1[] = "Edit #1 title:[Task Title";
    // char editCommand2[] = "Edit #2 description:Task Description]";
    // char editCommand3[] = "Edit #3 time:[T]ask Time]";
    
    // Only copy until reaching the max length to prevent unpredictable problems for next time we call extractBetweenBrackets()
    char editCommand1[] = "Edit #1 title:[Valid Task Title with length longer than MAX_SIZE_TITLE and copy only first 99 character, 1 for null-terminated-------end]";
    char editCommand2[] = "Edit #2 description:[Task Description]";
    char editCommand3[] = "Edit #3 time:[Task Time]";

    // Declare variables to store extracted information
    char title[MAX_SIZE_TITLE];
    char description[MAX_SIZE_DESCRIPTION];
    char time[MAX_SIZE_TIME];

    // Test the functions
    getTitleFromEdit(editCommand1, title);
    getDescriptionFromEdit(editCommand2, description);
    getTimeFromEdit(editCommand3, time);

    // Display the extracted information
    printf("Title: %s\n", title);
    printf("Description: %s\n", description);
    printf("Time: %s\n", time);

    return 0;
}
