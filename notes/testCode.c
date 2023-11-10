#include <stdio.h>
#include <string.h>

void extractBetweenBrackets(char *start, char *end, char *output) {
    if (start != NULL && end != NULL) {
        // Calculate the length of the content between square brackets
        size_t length = end - start - 1;
        // Copy the content to the output variable
        strncpy(output, start + 1, length);
        // Ensure null termination
        output[length] = '\0';
    }
}

int main() {
    // Test case
    char input[] = "[Some content that is larger than the destination]";
    char output[20];  // Destination with limited space

    // Call the function
    extractBetweenBrackets(input, strchr(input, '['), output);

    // Print the result
    printf("Extracted: %s\n", output);

    return 0;
}
