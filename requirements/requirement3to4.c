#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TITLE_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 200

// Function to check if the string is valid
int checkValidity(char *raw_string, size_t max_length) {
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
    return checkValidity(raw_title, MAX_TITLE_LENGTH);
}

// Function to check if the description is valid
int checkDescription(char *raw_description) {
    return checkValidity(raw_description, MAX_DESCRIPTION_LENGTH);
}

int main() {
    // Test cases
    char validTitle[] = "Programming Assignment 1";
    char invalidMaxLengthTitle[] = "A very long title exceeding the maximum lengthhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh";
    char invalidCharacterTitle[] = "Invalid#Title";
    char invalidStartWhitespaceTitle[] = " Invalid Start Whitespace";
    char invalidEndWhitespaceTitle[] = "Invalid End Whitespace ";

    char validDescription[] = "This is a valid description.";
    char invalidMaxLengthDescription[] = "A very long description exceeding the maximum lengthhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh.";
    char invalidCharacterDescription[] = "Invalid#Description";
    char invalidStartWhitespaceDescription[] = " Invalid Start Whitespace";
    char invalidEndWhitespaceDescription[] = "Invalid End Whitespace ";

    // Test the checkTitle and checkDescription functions
    printf("Title Test Cases:\n");
    printf("Valid Title: %d\n", checkTitle(validTitle));
    printf("Invalid Max Length Title: %d\n", checkTitle(invalidMaxLengthTitle));
    printf("Invalid Character Title: %d\n", checkTitle(invalidCharacterTitle));
    printf("Invalid Start Whitespace Title: %d\n", checkTitle(invalidStartWhitespaceTitle));
    printf("Invalid End Whitespace Title: %d\n\n", checkTitle(invalidEndWhitespaceTitle));

    printf("Description Test Cases:\n");
    printf("Valid Description: %d\n", checkDescription(validDescription));
    printf("Invalid Max Length Description: %d\n", checkDescription(invalidMaxLengthDescription));
    printf("Invalid Character Description: %d\n", checkDescription(invalidCharacterDescription));
    printf("Invalid Start Whitespace Description: %d\n", checkDescription(invalidStartWhitespaceDescription));
    printf("Invalid End Whitespace Description: %d\n", checkDescription(invalidEndWhitespaceDescription));

    return 0;
}
