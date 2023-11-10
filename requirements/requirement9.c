#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Enum to represent task statuses
typedef enum
{
    IN_PROGRESS,
    DONE,
    ARCHIVED,
    INVALID_STATUS
} Status;

#define FIXED_SIZE_STATUS 1

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

// Function to get the status from Edit command
Status getStatusFromEdit(char *edit_cmd)
{
    // Find the valid opening bracket in the Edit command
    char *start = strstr(edit_cmd, "status:[");
    // If there is no valid opening bracket, return an invalid status
    if (start == NULL) return INVALID_STATUS;
    // Find closing bracket
    char *end = strchr(start, ']');
    // If there is no valid opening bracket, return an invalid status
    if (end == NULL) return INVALID_STATUS;
    // Extract the status from the Edit command, only need 2 first characters if it's have more than 1, and 1 more to null-terminate, so sum is 3
    char extractedInsideBracket[3] = "";
    extractBetweenBrackets(start + strlen("status:"), end, extractedInsideBracket, 3);
    // Check if there's exactly 1 character extracted
    if (strlen(extractedInsideBracket) != FIXED_SIZE_STATUS) return INVALID_STATUS;
    // Convert the status character to lowercase for case-insensitive comparison
    char status = extractedInsideBracket[0];
    status = tolower(status);
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
        return INVALID_STATUS;
    }
}

int main()
{
    // Test cases
    char editCommand1[] = "Edit #1 status:[I]";
    char editCommand2[] = "Edit #2 status:[d]";
    char editCommand3[] = "Edit #3 status:[A]";
    char editCommand4[] = "Edit #4 status:[InvalidStatus]";

    // Test the function
    Status status1 = getStatusFromEdit(editCommand1);
    Status status2 = getStatusFromEdit(editCommand2);
    Status status3 = getStatusFromEdit(editCommand3);
    Status status4 = getStatusFromEdit(editCommand4);

    // Display the results
    printf("Status 1: %d\n", status1); // Output: Status 1: 0
    printf("Status 2: %d\n", status2); // Output: Status 2: 1
    printf("Status 3: %d\n", status3); // Output: Status 3: 2
    printf("Status 4: %d\n", status4); // Output: Status 4: 3

    return 0;
}

