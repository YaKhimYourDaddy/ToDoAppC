#include <stdio.h>
#include <string.h>

// Enum to represent command types
typedef enum {
    ADD,
    EDIT,
    SHOW,
    DELETE,
    QUIT,
    INVALID
} CommandType;

// Function to get the command type
CommandType getCommandType(char *command) {
    // Assuming the maximum length of the first word is 10
    char firstWord[10];

    // Extract the first word from the command
    // int i = 0;
    // while (command[i] != '\0' && command[i] != ' ' && i < 10) {
    //     firstWord[i] = command[i];
    //     i++;
    // }
    // firstWord[i] = '\0';
    // You can use this below line instead above code 
    // if you want " Quit" is QUIT instead of INVALID
    sscanf(command, "%s", firstWord);


    // Compare the first word with command types
    if (strcmp(firstWord, "Add") == 0)
        return ADD;
    if (strcmp(firstWord, "Edit") == 0)
        return EDIT;
    if (strcmp(firstWord, "Show") == 0)
        return SHOW;
    if (strcmp(firstWord, "Delete") == 0)
        return DELETE;
    if (strcmp(firstWord, "Quit") == 0)
        return QUIT;
    // Default case for invalid commands
    return INVALID;
}

// Testing the getCommandType function
int main() {
    char command1[] = "Add data";
    char command2[] = "Edit entry";
    char command3[] = "Show all";
    char command4[] = "Delete item";
    char command5[] = "Quit";
    char command6[] = "Invalid command";
    char command7[] = "Addd data";
    char command8[] = "edit entry";
    char command9[] = "SHOW all";
    char command10[] = "Dele";
    char command11[] = "  Quit ";
    char command12[] = "random string";

    // Test cases
    printf("Command 1 Type: %d\n", getCommandType(command1));
    printf("Command 2 Type: %d\n", getCommandType(command2));
    printf("Command 3 Type: %d\n", getCommandType(command3));
    printf("Command 4 Type: %d\n", getCommandType(command4));
    printf("Command 5 Type: %d\n", getCommandType(command5));
    printf("Command 6 Type: %d\n", getCommandType(command6));
    printf("Command 7 Type: %d\n", getCommandType(command7));
    printf("Command 8 Type: %d\n", getCommandType(command8));
    printf("Command 9 Type: %d\n", getCommandType(command9));
    printf("Command 10 Type: %d\n", getCommandType(command10));
    printf("Command 11 Type: %d\n", getCommandType(command11));
    printf("Command 12 Type: %d\n", getCommandType(command12));

    return 0;
}
