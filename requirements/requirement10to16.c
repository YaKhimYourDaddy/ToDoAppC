#include <stdio.h>
#include <string.h>

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
struct Task
{
    int num;
    char title[MAX_SIZE_TITLE];
    char description[MAX_SIZE_DESCRIPTION];
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

// Requirement 11: Print task by task number
void printTaskByNum(struct Task *array_tasks, int no_tasks, int num)
{
    if (num < 1)
    {
        printf("%d is invalid input because #num must be positive\n", num);
        return;
    }
    for (int i = 0; i < no_tasks; ++i)
    {
        if (array_tasks[i].num == num)
        {
            printTask(&array_tasks[i]);
            return; // Assuming task numbers are unique, so we can exit early
        }
    }
    printf("Task #%d not found\n", num);
}

// Requirement 12: Print the first quan tasks
void printHeadTasks(struct Task *array_tasks, int no_tasks, int quan)
{
    int endIndex = (quan < no_tasks) ? quan : no_tasks;
    for (int i = 0; i < endIndex; ++i)
    {
        printTask(&array_tasks[i]);
    }
}

// Requirement 13: Print the last quan tasks
void printTailTasks(struct Task *array_tasks, int no_tasks, int quan)
{
    int startIndex = (quan < no_tasks) ? no_tasks - quan : 0;
    for (int i = startIndex; i < no_tasks; ++i)
    {
        printTask(&array_tasks[i]);
    }
}

// Function to print tasks filtered by title
void printFilteredTasksByTitle(struct Task *array_tasks, int no_tasks, const char *filter_title)
{
    if (filter_title == NULL || *filter_title == '\0')
    {
        printAllTasks(array_tasks, no_tasks);
        return;
    }
    // Non-empty filter_title, search for tasks with matching titles
    for (int i = 0; i < no_tasks; ++i)
    {
        if (strstr(array_tasks[i].title, filter_title) != NULL)
        {
            printTask(&array_tasks[i]);
        }
    }
}

// Requirement 15: Print tasks filtered by description
void printFilteredTasksByDescription(struct Task *array_tasks, int no_tasks, char *filter_description)
{
    if (filter_description == NULL || *filter_description == '\0')
    {
        printAllTasks(array_tasks, no_tasks);
        return;
    }
    // Non-empty filter_title, search for tasks with matching titles
    for (int i = 0; i < no_tasks; ++i)
    {
        if (strstr(array_tasks[i].description, filter_description) != NULL)
        {
            printTask(&array_tasks[i]);
        }
    }
}

// Requirement 16: Print tasks filtered by status
void printFilteredTasksByStatus(struct Task *array_tasks, int no_tasks, Status filter_status)
{
    for (int i = 0; i < no_tasks; ++i)
    {
        if (array_tasks[i].status == filter_status)
        {
            printTask(&array_tasks[i]);
        }
    }
}

// have not handle:
//
int main()
{
    // Example usage
    struct Task tasks[] = {
        {1, "Title 1", "Description 1", IN_PROGRESS},
        {2, "Title 2", "Description 2", DONE},
        {3, "Title 3", "Description 3", ARCHIVED},
        {4, "TTTTitle 4", "Description 4", INVALID_STATUS},
        {5, "title 5", "Description 5", IN_PROGRESS},
        {6, "Task 6", "Description 6", DONE},
        {7, "Task 7", "Description 7", ARCHIVED},
        {8, "Task 8", "Description 8", INVALID_STATUS},
        {9, "Task 9", "Description 9", IN_PROGRESS},
        {10, "Task 10", "Description 10", DONE},
        {11, "Task 11", "Description 11", ARCHIVED},
        {12, "Task 12", "Description 12", INVALID_STATUS},
    };

    int num_tasks = sizeof(tasks) / sizeof(tasks[0]);

    // printf("\nprintAllTasks(tasks, num_tasks);");
    // printAllTasks(tasks, num_tasks);




    // printf("\nprintTaskByNum(tasks, sizeof(tasks) / sizeof(tasks[0]), 2);\n");
    // printTaskByNum(tasks, sizeof(tasks) / sizeof(tasks[0]), 2);

    // printf("\nprintTaskByNum(tasks, sizeof(tasks) / sizeof(tasks[0]), 0);\n");
    // printTaskByNum(tasks, sizeof(tasks) / sizeof(tasks[0]), 0);

    // printf("\nprintTaskByNum(tasks, sizeof(tasks) / sizeof(tasks[0]), -1);\n");
    // printTaskByNum(tasks, sizeof(tasks) / sizeof(tasks[0]), -1);

    // printf("\nprintTaskByNum(tasks, sizeof(tasks) / sizeof(tasks[0]), num_task + 1);\n");
    // printTaskByNum(tasks, sizeof(tasks) / sizeof(tasks[0]), num_tasks + 1);




    // printf("\nprintHeadTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), 2);\n");
    // printHeadTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), 2);

    // printf("\nprintHeadTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), num_task + 1);\n");
    // printHeadTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), num_tasks + 1);

    // printf("\nprintHeadTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), 0);\n");
    // printHeadTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), 0);

    // printf("\nprintHeadTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), -1);\n");
    // printHeadTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), -1);




    // printf("\nprintTailTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), num_task + 1);\n");
    // printTailTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), num_tasks + 1);

    // printf("\nprintTailTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), 3);\n");
    // printTailTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), 3);

    // printf("\nprintTailTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), -1);\n");
    // printTailTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), -1);

    // printf("\nprintTailTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), 0);\n");
    // printTailTasks(tasks, sizeof(tasks) / sizeof(tasks[0]), 0);




    // printf("\nprintFilteredTasksByTitle(); // Title\n");
    // printFilteredTasksByTitle(tasks, sizeof(tasks) / sizeof(tasks[0]), "Title");

    // printf("\nprintFilteredTasksByTitle(); // Title 1\n");
    // printFilteredTasksByTitle(tasks, sizeof(tasks) / sizeof(tasks[0]), "Title 1");

    // printf("\nprintFilteredTasksByTitle(); // title 1\n");
    // printFilteredTasksByTitle(tasks, sizeof(tasks) / sizeof(tasks[0]), "title 1");

    // printf("\nprintFilteredTasksByTitle(); // Task 12222\n");
    // printFilteredTasksByTitle(tasks, sizeof(tasks) / sizeof(tasks[0]), "Task 12222");

    // printf("\nprintFilteredTasksByTitle(); // null string\n");
    // printFilteredTasksByTitle(tasks, sizeof(tasks) / sizeof(tasks[0]), ""); // valid input, print all

    // printf("\nprintFilteredTasksByTitle(); // null string or null terminator\n");
    // printFilteredTasksByTitle(tasks, sizeof(tasks) / sizeof(tasks[0]), ""); // valid input, print all

    // printf("\nprintFilteredTasksByTitle(); // null pointer\n");
    // printFilteredTasksByTitle(tasks, sizeof(tasks) / sizeof(tasks[0]), NULL); // valid input until strstr() so I print all, no need to run into strstr()

    // printf("\nprintFilteredTasksByTitle(); // number but be treated as character by ascii\n");
    // printFilteredTasksByTitle(tasks, sizeof(tasks) / sizeof(tasks[0]), 61); // invalid input to us but not to the compiler, warning, still run, stop right after passing arguments, print nothing

    
    
    
    // printf("\nprintFilteredTasksByDescription(); // Des\n");
    // printFilteredTasksByDescription(tasks, sizeof(tasks) / sizeof(tasks[0]), "Des");

    // printf("\nprintFilteredTasksByDescription(); // Description 1\n");
    // printFilteredTasksByDescription(tasks, sizeof(tasks) / sizeof(tasks[0]), "Description 1");

    // printf("\nprintFilteredTasksByDescription(); // description 1\n");
    // printFilteredTasksByDescription(tasks, sizeof(tasks) / sizeof(tasks[0]), "description 1");

    // printf("\nprintFilteredTasksByDescription(); // Description 12222\n");
    // printFilteredTasksByDescription(tasks, sizeof(tasks) / sizeof(tasks[0]), "Description 12222");

    // printf("\nprintFilteredTasksByDescription(); // null string\n");
    // printFilteredTasksByDescription(tasks, sizeof(tasks) / sizeof(tasks[0]), ""); // valid input, print all

    // printf("\nprintFilteredTasksByDescription(); // null string or null terminator\n");
    // printFilteredTasksByDescription(tasks, sizeof(tasks) / sizeof(tasks[0]), ""); // valid input, print all

    // printf("\nprintFilteredTasksByDescription(); // null pointer\n");
    // printFilteredTasksByDescription(tasks, sizeof(tasks) / sizeof(tasks[0]), NULL); // valid input until strstr() so I print all, no need to run into strstr()

    // printf("\nprintFilteredTasksByDescription(); // number but be treated as character by ascii\n");
    // printFilteredTasksByDescription(tasks, sizeof(tasks) / sizeof(tasks[0]), 61); // invalid input to us but not to the compiler, warning, still run, stop right after passing arguments, print nothing
    
    
    
    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), DONE);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), DONE);
        
    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), IN_PROGRESS);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), IN_PROGRESS);
        
    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), ARCHIVED);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), ARCHIVED);
        
    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), INVALID_STATUS);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), INVALID_STATUS);
        
    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), 1);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), 1);
        
    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), -1);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), -1); 

    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), 4);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), 4);

    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), 0.2);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), 0.2);

    // enum AnotherEnum {
    //     ITEM1,
    //     ITEM2,
    //     ITEM3,
    //     ITEM4,
    //     ITEM5
    // };
    // enum AnotherEnum anotherEnumElement1 = ITEM1;
    // enum AnotherEnum anotherEnumElement2 = ITEM2;
    // enum AnotherEnum anotherEnumElement5 = ITEM5;
    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), anotherEnumElement1);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), anotherEnumElement1);
    
    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), anotherEnumElement2);\n"); 
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), anotherEnumElement2); // to see if there's a problem after first test

    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), anotherEnumElement5);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), anotherEnumElement5); // out of range, no show, still run, no crash

    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), ITEM1);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), ITEM1); // still valid like anotherEnumElement1

    // printf("\nprintFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), ITEM5);\n");
    // printFilteredTasksByStatus(tasks, sizeof(tasks) / sizeof(tasks[0]), ITEM5); // out of range, no show, still run, no crash


    return 0;
}
