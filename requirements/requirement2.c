#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to extract information between square brackets
void extractBetweenBrackets(char *start, char *end, char *output)
{
    if (start != NULL && end != NULL)
    {
        // Calculate the length of the content between square brackets
        size_t length = end - start - 1;
        // Copy the content to the output variable
        strncpy(output, start + 1, length);
        // Null-terminate the extracted content
        output[length] = '\0';
    }
}

// Function to extract title from Add command
void getTitleFromAdd(char *command, char *out_title)
{
    // Find the first square bracket pair of <title>
    char *start = strchr(command, '[');
    char *end = strchr(start, ']');
    
    // Let out_title NULL if can't find closing bracket
    if (end == NULL)
    {
        out_title[0] = '\0';
        return;
    }

    extractBetweenBrackets(start, end, out_title);
}

// Function to extract description from Add command
void getDescriptionFromAdd(char *command, char *out_description)
{
    // Find the first square bracket pair of <title>
    char *start = strchr(command, '[');
    char *end = strchr(start, ']');
    
    // Let out_description NULL if can't find closing bracket for title
    if (end == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    // Find the second square bracket pair of <description>
    start = strchr(end + 1, '[');
    end = strchr(start, ']');

    // Let out_description NULL if can't find closing bracket for description
    if (end == NULL)
    {
        out_description[0] = '\0';
        return;
    }

    extractBetweenBrackets(start, end, out_description);
}

// Function to extract time from Add command
void getTimeFromAdd(char *command, char *out_time)
{
    // Find the first square bracket pair of <title>
    char *start = strchr(command, '[');
    char *end = strchr(start, ']');
    
    // Let out_time NULL if can't find closing bracket for title
    if (end == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    // Find the second square bracket pair of <description>
    start = strchr(end + 1, '[');
    end = strchr(start, ']');

    // Let out_time NULL if can't find closing bracket for description
    if (end == NULL)
    {
        out_time[0] = '\0';
        return;
    }
        
    // Find the third square bracket pair of <time>
    start = strchr(end + 1, '[');
    end = strchr(start, ']');

    // Let out_time NULL if can't find closing bracket for time
    if (end == NULL)
    {
        out_time[0] = '\0';
        return;
    }

    extractBetweenBrackets(start, end, out_time);
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
        "Add [[title] [description] [time]]"  ,  // invalid
    };

    for (int i = 0; i < 7; ++i) {
        char title[100];
        char description[100];
        char time[100];

        getTitleFromAdd(testCases[i], title);
        getDescriptionFromAdd(testCases[i], description);
        getTimeFromAdd(testCases[i], time);

        printf("\nTest Case %d:\n", i + 1);
        printf("Title: %s\n", title);
        printf("Description: %s\n", description);
        printf("Time: %s\n\n", time);
    }

    return 0;
}



