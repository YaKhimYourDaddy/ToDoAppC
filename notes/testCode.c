#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_NO_TASKS 100

bool addTask(struct Task *array_tasks, int no_tasks, char *new_title, char *new_description, char *new_time)
{
    size_t arraySize = sizeof(array_tasks) / sizeof(array_tasks[0]);
    if (arraySize < MAX_NO_TASKS)
    {
        // Reallocate the array with size of MAX_NO_TASKS
        // Copy old elements
        // Add new elements
    }

    // Check if there is space for a new task
    if (no_tasks > MAX_NO_TASKS)
        return false;

    // Set values for the new task
    (array_tasks[no_tasks])->num = no_tasks + 1;
    safeStringCopy(array_tasks[no_tasks]->title, new_title, MAX_SIZE_TITLE);
    safeStringCopy(array_tasks[no_tasks]->description, new_description, MAX_SIZE_DESCRIPTION);
    safeStringCopy(array_tasks[no_tasks]->time, new_time, MAX_SIZE_TIME);
    (array_tasks[no_tasks])->status = IN_PROGRESS;
    return true;
    
}



