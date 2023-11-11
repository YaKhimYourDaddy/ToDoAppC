#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define MAX_NO_TASKS 9
#define MAX_SIZE_TITLE 100
#define MAX_SIZE_DESCRIPTION 100
#define MAX_SIZE_TIME 100
// Enum to represent task statuses
typedef enum
{
    IN_PROGRESS,
    DONE,
    ARCHIVED,
    INVALID_STATUS
} Status;

// Global variable for status strings
const char *statusStrings[] = {"In Progress", "Done", "Archived", "Invalid Status"};

// Structure to represent a task
struct Task {
    int num;
    char title[MAX_SIZE_TITLE];  // Adjust the size as needed
    char description[MAX_SIZE_DESCRIPTION];  // Adjust the size as needed
    char time[MAX_SIZE_TIME];  // Adjust the size as needed
    Status status;
};

// Function to display information of a Task
void printTask(struct Task *task)
{
    printf("Task #%d\n", task->num);
    printf("Title: %s\n", task->title);
    printf("Description: %s\n", task->description);
    printf("Status: %s\n", statusStrings[task->status]);
    printf("-----------\n");
}

// Requirement 10: Function to display all tasks in the array
void printAllTasks(struct Task *array_tasks, int no_tasks)
{
    for (int i = 0; i < no_tasks; ++i)
    {
        printTask(&array_tasks[i]);
    }
}

// Function to safely copy strings
void safeStringCopy(char *dest, const char *src, size_t destSize) {
    if (dest != NULL && src != NULL && destSize > 0) {
        strncpy(dest, src, destSize - 1);  // Leave space for the null terminator
        dest[destSize - 1] = '\0';  // Ensure null-terminated
    }
}

// Function to copy a task
void copyTask(struct Task *dest, const struct Task *src)
{
    // dest->num = src->num;  // no need and should not to copy num
    safeStringCopy(dest->title, src->title, sizeof(dest->title));
    safeStringCopy(dest->description, src->description, sizeof(dest->description));
    dest->status = src->status;
}

// Function to delete a task by num
bool deleteTask(struct Task *array_tasks, int *no_tasks, int num)
{
    // Check if the task with the given num exists
    int index = -1;
    for (int i = 0; i < *no_tasks; ++i)
    {
        if (array_tasks[i].num == num)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        // Task with the given num not found
        return false;
    }

    // Shift elements to fill the gap left by the deleted task
    for (int i = index; i < *no_tasks - 1; ++i)
    {
        copyTask(&array_tasks[i], &array_tasks[i + 1]);
        // copyTask() does not copy num, so no need to decrease the num
    }

    // Update the number of tasks
    (*no_tasks)--;

    return true;
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

// Function to delete task and print tasks
void deleteAndPrint(struct Task *tasks, int *no_tasks, int num)
{
    bool deleted = deleteTask(tasks, no_tasks, num);
    printf("\nDeleting task with num = %d\n", num);
    if (deleted)
    {
        printf("Tasks after deletion:\n");
        printAllTasks(tasks, *no_tasks);
    }
    else
    {
        printf("Task with num = %d not found. No changes.\n", num);
    }
}

int main()
{
    // Example usage of the functions
    struct Task tasks[10];
    int no_tasks = 0; // Initialize with the number of tasks

    // Adding 10 tasks
    addTask(tasks, &no_tasks, "Task 1", "Description 1", "2023-11-10 12:00");
    addTask(tasks, &no_tasks, "Task 2", "Description 2", "2023-11-10 12:15");
    addTask(tasks, &no_tasks, "Task 3", "Description 3", "2023-11-10 12:30");
    addTask(tasks, &no_tasks, "Task 4", "Description 4", "2023-11-10 12:45");


    // Display tasks before deletion
    printf("Tasks before deletion:\n");
    printAllTasks(tasks, no_tasks);

    // Case: Delete task with num = 1
    deleteAndPrint(tasks, &no_tasks, 1);

    // Case: Delete task with num = no_tasks
    deleteAndPrint(tasks, &no_tasks, no_tasks);

    // Case: Delete task with num = 0
    deleteAndPrint(tasks, &no_tasks, 0);

    // Case: Delete task with num = -1
    deleteAndPrint(tasks, &no_tasks, -1);

    // Case: Delete task with num = 3.3
    deleteAndPrint(tasks, &no_tasks, 1.3); // 1.3 will be 1

    // Case: Delete task with num = no_tasks + 1
    deleteAndPrint(tasks, &no_tasks, no_tasks + 1); 

    // Case: Delete task when task list is empty
    deleteAndPrint(tasks, &no_tasks, 1); // delete the last one 
    deleteAndPrint(tasks, &no_tasks, 0); // not found with what num ever passed

    return 0;
}
