#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *str1 = "-a123";
    const char *str2 = "ab";
    const char *str3 = "   ab1";

    int num1 = atoi(str1); // Converts "123" to the integer 123
    int num2 = atoi(str2); // Converts "-456" to the integer -456
    int num3 = atoi(str3); // Converts "789" to the integer 789 (skips leading spaces)

    printf("num1: %d\n", num1); // Output: num1: 123
    printf("num2: %d\n", num2); // Output: num2: -456
    printf("num3: %d\n", num3); // Output: num3: 789

    return 0;
}
