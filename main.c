/*

Program Description: A simple to-do/task manager in the terminal
Author: Noel Ardelean
Date: 2/12/24

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TASKS 10
#define MAX_TASK_LENGTH 256
#define FILENAME "tasks.txt"

char tasks[MAX_TASKS][MAX_TASK_LENGTH];
int num_tasks = 0;

// Function to save tasks to a file
void save_tasks()
{

    // Open the file or create the file if it doesn't already exist
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;

        // Write the number of tasks to the file. This makes it easier for program to know how many tasks to load later when you restart it
        fprintf(file, "%d\n", num_tasks);
    }

    // Print each task on a new line
    for (int i = 0; i < num_tasks; i++)
    {
        fprintf(file, "%s\n", tasks[i]);
    }

    // Close the file to ensure all data is saved and no resource leaks
    fclose(file);
    printf("Tasks succesfully saved");
}

// Function to load tasks from a file
void load_tasks()
{
    // Open the file and read it
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        return;
    }

    // Read the number of tasks from the file
    if (fscanf(file, "%d\n", &num_tasks) != 1)
    {
        printf("No tasks found\n");
        fclose(file);
        return;
    }

    // Read each task from the file
    for (int i = 0; i < num_tasks; i++)
    {
        if (fgets(tasks[i], MAX_TASK_LENGTH, file) == NULL)
        {
            printf("Error reading tasks\n");

            // If there is an error this updates num_tasks to the number of tasks successfully read so far to prevent invalid data
            num_tasks = i;
            break;
        }

        // Remove the newline character at the end of the task with \0 (Null character)
        tasks[i][strcspn(tasks[i], "\n")] = 0;
    }

    // Close the file
    fclose(file);
    printf("%d tasks loaded", num_tasks);
}

// Function to add tasks
void add_task(char *task /* Expects a string */)
{
    if (num_tasks < MAX_TASKS)
    {
        // If there is enough space for tasks, take the oncoming task argument and copy it into tasks[num_tasks] and with a limit of MAX_TASK_LENGTH
        strncpy(tasks[num_tasks], task, MAX_TASK_LENGTH);
        num_tasks++;
        printf("Task added\n");
        save_tasks();
    }
}

// Function to list tasks
void list_tasks()
{
    if (num_tasks == 0)
    {
        printf("No tasks available.\n");
    }
    else
    {
        for (int i = 0; i < num_tasks; i++)
        {
            printf("%d. %s\n", i, tasks[i]);
        }
    }
}

// Function to delete tasks
void remove_task(int task_index)
{
    if (task_index >= 0 && task_index < num_tasks)
    {
    }
}

int main()
{

    return 0;
}