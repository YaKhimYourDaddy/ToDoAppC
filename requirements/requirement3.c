#include <stdio.h>

// Function to check if the title is valid according to specified conditions
int checkTitle(char* raw_title) {
    int length = 0;

    // Check each character in the title
    while (*raw_title != '\0') {
        // Check maximum length condition
        if (length >= 100) {
            return length;
        }

        // Check character types
        if (!(((*raw_title >= 'a' && *raw_title <= 'z') || (*raw_title >= 'A' && *raw_title <= 'Z') ||
               (*raw_title >= '0' && *raw_title <= '9') || *raw_title == ' ' || *raw_title == ',' ||
               *raw_title == '.' || *raw_title == '-' || *raw_title == ':' || *raw_title == '|' ||
               *raw_title == '/'))) {
            return length;  // Return position of the first invalid character
        }

        // Check leading and trailing whitespace
        if (length == 0 && (*raw_title == ' ' || *raw_title == '\t')) {
            return length;  // Return position of leading whitespace
        }

        if (*(raw_title + 1) == '\0' && (*raw_title == ' ' || *raw_title == '\t')) {
            return length;  // Return position of trailing whitespace
        }

        raw_title++;
        length++;
    }

    // Check if the title is empty
    if (length == 0) {
        return 0;  // Return 0 for an empty title
    }

    // Title is valid
    return -1;
}

int main() {
    char raw_title[100];  // Assuming a maximum input size of 100 characters

    // Get user input
    printf("Enter the title: ");
    fgets(raw_title, sizeof(raw_title), stdin);

    // Remove the newline character from the input
    int len = 0;
    while (raw_title[len] != '\n' && raw_title[len] != '\0') {
        len++;
    }
    raw_title[len] = '\0';

    // Check the title using the function
    int result = checkTitle(raw_title);

    // Print the result
    if (result == -1) {
        printf("Title is valid.\n");
    } else if (result == 0) {
        printf("Error: Title is empty.\n");
    } else {
        printf("Error: Title is invalid at position %d.\n", result);
    }

    return 0;
}
