#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define MAX_NO_TASKS 99
#define MAX_SIZE_TITLE 100
#define MAX_SIZE_DESCRIPTION 200
#define MAX_SIZE_TIME 33
// Enum to represent task statuses
typedef enum {
    IN_PROGRESS,
    DONE,
    ARCHIVED
} Status;

// Structure to represent a task
struct Task {
    int num;
    char title[MAX_SIZE_TITLE];  // Adjust the size as needed
    char description[MAX_SIZE_DESCRIPTION];  // Adjust the size as needed
    char time[MAX_SIZE_TIME];  // Adjust the size as needed
    Status status;
};

// Function to safely copy strings
void safeStringCopy(char *dest, const char *src, size_t destSize) {
    if (dest != NULL && src != NULL && destSize > 0) {
        strncpy(dest, src, destSize - 1);  // Leave space for the null terminator
        dest[destSize - 1] = '\0';  // Ensure null-terminated
    }
}

// Function to add a new task to the array
bool addTask(struct Task *array_tasks, int *no_tasks, char *new_title, char *new_description, char *new_time) {
    // Check if there is space for a new task
    if (*no_tasks < MAX_NO_TASKS) {
        // Set values for the new task
        array_tasks[*no_tasks].num = *no_tasks + 1;
        safeStringCopy(array_tasks[*no_tasks].title, new_title, MAX_SIZE_TITLE);
        safeStringCopy(array_tasks[*no_tasks].description, new_description, MAX_SIZE_DESCRIPTION);
        safeStringCopy(array_tasks[*no_tasks].time, new_time, MAX_SIZE_TIME);
        array_tasks[*no_tasks].status = IN_PROGRESS;

        // Increment the number of tasks
        (*no_tasks)++;

        // Return true to indicate success
        return true;
    }
    return false;
}


int main() {
    // Example usage
    struct Task tasks[MAX_NO_TASKS];
    int no_of_tasks = 0;

    // Adding 10 tasks
    addTask(tasks, &no_of_tasks, "Task 1", "Description 1", "2023-11-10 12:00");
    addTask(tasks, &no_of_tasks, "Task 2 with length >= MAX_SIZE_TITLE to test buffer---------------100char------------------------end" 
, "Description 2", "2023-11-10 12:15");  // src 100char, dest 99char get copied, we have to null-terminate the destinate string
    addTask(tasks, &no_of_tasks, "Task 2 with length < MAX_SIZE_TITLE to test buffer----------------99char------------------------end"
, "Description 3", "2023-11-10 12:30");  // src 99char, dest 99char get copied, we have to null-terminate the destinate string
    addTask(tasks, &no_of_tasks, "Task 4", "Description 4", "2023-11-10 12:45");
    addTask(tasks, &no_of_tasks, "Task 5", "Description 5", "2023-11-10 13:00");
    addTask(tasks, &no_of_tasks, "Task 6", "Description 6", "2023-11-10 13:15");
    addTask(tasks, &no_of_tasks, "Task 7", "Description 7", "2023-11-10 13:30");
    addTask(tasks, &no_of_tasks, "Task 8", "Description 8", "2023-11-10 13:45");
    addTask(tasks, &no_of_tasks, "Task 9", "Description 9", "2023-11-10 14:00");
    addTask(tasks, &no_of_tasks, "Task 10", "Description 10", "2023-11-10 14:15");

    // Display the added tasks
    for (int i = 0; i < no_of_tasks; ++i) {
        printf("Task#%d: %s, %s, %s\n", tasks[i].num, tasks[i].title, tasks[i].description, tasks[i].time);
    }

    return 0;
}