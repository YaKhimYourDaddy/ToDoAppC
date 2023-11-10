#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to extract <num> from Edit command
int getNumFromCommand(char *command)
{
    // Find the '#' character in the command
    char *numStart = strchr(command, '#');

    if (numStart == NULL)
    {
        // If the command does not contain the '#' character, return -1
        return -1;
    }

    // Extract the substring starting from '#' (excluding '#')
    char numString[10]; // Assuming the maximum length of <num> is 10

    // numStart + 1: numStart is memory of #, so I set + 1 to skip #
    // %9: at most 9 characters should be read (to avoid buffer overflow because of numString[10]). 
    // [^ ]: It specifies a character set to match. In this case, it says "match any character except space (' ')".
    // So, it will read characters until it encounters a space.
    // numString: This is the destination variable where the read characters will be stored.
    sscanf(numStart + 1, "%9[^ ]", numString);

    // Convert the extracted string to an integer
    int num = atoi(numString);

    // Check if the conversion was successful and the value is a positive integer
    if (num <= 0) return 0; 

    return num;
}

int main()
{
    // Test cases
    char editCommand1[] = "Edit #1 title:[Task Title]";
    char editCommand2[] = "Edit #ab12 title:[Task Title]";
    char editCommand3[] = "Edit title:[Task Title]";
    char editCommand4[] = "Edit # -10 title:[Task Title]";
    char editCommand5[] = "Edit #0.123 title:[Task Title]";
    char editCommand6[] = "Edit #12bd title:[Task Title]";

    // Test the function
    int num1 = getNumFromCommand(editCommand1);
    int num2 = getNumFromCommand(editCommand2);
    int num3 = getNumFromCommand(editCommand3);
    int num4 = getNumFromCommand(editCommand4);
    int num5 = getNumFromCommand(editCommand5);
    int num6 = getNumFromCommand(editCommand6);

    // Display the results
    printf("Num 1: %d\n", num1); // Output: Num 1: 1
    printf("Num 2: %d\n", num2); // Output: Num 2: 0
    printf("Num 3: %d\n", num3); // Output: Num 3: -1
    printf("Num 4: %d\n", num4); // Output: Num 4: 0
    printf("Num 5: %d\n", num5); // Output: Num 5: 0
    printf("Num 6: %d\n", num6); // Output: Num 6: 12

    return 0;
}
