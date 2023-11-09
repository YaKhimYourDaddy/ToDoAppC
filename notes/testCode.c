#include <stdio.h>
#include <stdbool.h>

// Function to check if addCommand contains three separated brackets
bool isValidAddCommand(char *addCommand) {
    int count = 0;
    char *ptr = addCommand;

    while (*ptr != '\0') {
        if (*ptr == '[' && (ptr == addCommand || *(ptr - 1) != '[') && *(ptr + 1) != '[') {
            // Check if the opening bracket is outside any other brackets and not followed by another opening bracket
            count++;
        } else if (*ptr == ']' && ptr != addCommand && *(ptr - 1) != ']' && *(ptr + 1) != ']') {
            // Check if the closing bracket is outside any other brackets and not followed by another closing bracket
            count--;
        }

        ptr++;
    }

    return count == 3;
}

int main() {
    char testCases[][100] = {
        "Add [title] [description] [time]",            // valid
        "Add [title] [description] [[time]",            // valid
        "Add [title] [[description] [time]]",            // valid
        "Add [title] [description] [time]",            // valid
        "Add [title] [description [time]",              // invalid
        "Add [title] [description] [time",              // invalid
        "Add [[] [] []] [description] time",            // invalid
        "Add [[] [] []] [description] [time]",          // valid
        "Add [[] [] []] [description [time]",           // invalid
        "Add [[] [] []] [description] [time",           // invalid
        "Add [[] [] []] [description] time]",           // invalid
        "Add [[] []] [[]] [time]",                      // valid
        "Add [[title] [description] [time]]",          // invalid
    };

    for (int i = 0; i < 10; ++i) {
        printf("Test Case %d: %s\n", i + 1, isValidAddCommand(testCases[i]) ? "valid" : "invalid");
    }

    return 0;
}
