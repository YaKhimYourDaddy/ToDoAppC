#include <stdio.h>
#include <string.h>

// Function to get the field to be changed from Edit command
int getFieldFromEdit(char *edit_cmd) {
    // Find the first whitespace in the Edit command
    char *firstSpace = strchr(edit_cmd, ' ');
    if (firstSpace == NULL) {
        // If there is no first whitespace, the command is invalid
        return 0;
    }

    // Find the second whitespace in the Edit command
    // + 1 to skip the first whitespace
    char *secondSpace = strchr(firstSpace + 1, ' ');
    if (secondSpace == NULL) {
        // If there is no second whitespace, the command is invalid
        return 0;
    }

    // Find the colon in the Edit command
    char *colon = strchr(secondSpace, ':');
    if (colon == NULL) {
        // If there is no colon, the command is invalid
        return 0;
    }

    // Extract the field to be changed
    char field[20]; // Assuming the maximum length of the field is 20

    //strcpy(source string, begin location, number of character to copy)
    strncpy(field, secondSpace + 1, colon - secondSpace - 1);

    // Null-terminate the extracted field
    field[colon - secondSpace - 1] = '\0'; 

    // Compare the extracted field with valid strings
    if (strcmp(field, "title") == 0)
        return 1;
    if (strcmp(field, "description") == 0)
        return 2;
    if (strcmp(field, "time") == 0)
        return 3;
    if (strcmp(field, "status") == 0)
        return 4;
    // If the field is invalid, return 0
    return 0;
}

int main() {
    // Test cases
    char editCommand1[] = "Edit #1 title:[Task Title]";
    char editCommand2[] = "Edit #2 description:[Task Description]";
    char editCommand3[] = "Edit #3 time:[Task Time]";
    char editCommand4[] = "Edit #4 status:[Task Status]";
    char editCommand5[] = "Edit #5 invalid:[Invalid Field]";
    char editCommand6[] = "Edit  title:[content]]";
    char editCommand7[] = "   title:[content]";
    char editCommand8[] = "  :invalid:[content]";
    char editCommand9[] = "Edit #9[abcd title:]";
    char editCommand10[] = "Edit#10  title:[content]";
    char editCommand11[] = " #11 title:[content]";

    // Test the function
    int field1 = getFieldFromEdit(editCommand1);
    int field2 = getFieldFromEdit(editCommand2);
    int field3 = getFieldFromEdit(editCommand3);
    int field4 = getFieldFromEdit(editCommand4);
    int field5 = getFieldFromEdit(editCommand5);
    int field6 = getFieldFromEdit(editCommand6);
    int field7 = getFieldFromEdit(editCommand7);
    int field8 = getFieldFromEdit(editCommand8);
    int field9 = getFieldFromEdit(editCommand9);
    int field10 = getFieldFromEdit(editCommand10);
    int field11 = getFieldFromEdit(editCommand11);

    // Display the results
    printf("Field 1: %d\n", field1); // Output: Field 1: 1
    printf("Field 2: %d\n", field2); // Output: Field 2: 2
    printf("Field 3: %d\n", field3); // Output: Field 3: 3
    printf("Field 4: %d\n", field4); // Output: Field 4: 4
    printf("Field 5: %d\n", field5); // Output: Field 5: 0
    printf("Field 6: %d\n", field6); // Output: Field 6: 1
    printf("Field 7: %d\n", field7); // Output: Field 7: 0
    printf("Field 8: %d\n", field8); // Output: Field 8: 0
    printf("Field 9: %d\n", field9); // Output: Field 9: 1
    printf("Field 10: %d\n", field10); // Output: Field 10: 1
    printf("Field 11: %d\n", field11); // Output: Field 11: 1

    return 0;
}
