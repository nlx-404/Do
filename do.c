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
        printf("Error opening file.\n");
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
        printf("No tasks found.\n");
        fclose(file);
        return;
    }

    // Read each task from the file
    for (int i = 0; i < num_tasks; i++)
    {
        if (fgets(tasks[i], MAX_TASK_LENGTH, file) == NULL)
        {
            printf("Error reading tasks.\n");

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
        printf("Task added.\n");
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
    // If it is a valid task copy the contents of the task after it into its old place - basically shifting each element down
    if (task_index >= 0 && task_index < num_tasks)
    {
        for (int i = task_index; i < num_tasks - 1; i++)
        {
            strncpy(tasks[i], tasks[i + 1], MAX_TASK_LENGTH);
        }
        num_tasks--;
        printf("Task %d removed.\n", task_index);
        save_tasks();
    }
    else
    {
        printf("Invalid task selected.\n");
    }
}

// Function to clear all tasks
void clear_tasks()
{
    // Method 1: Resets task count to 0 and program thinks there is no tasks and when tasks are added they're overwritten in the file
    num_tasks = 0;
    printf("All tasks cleared.\n");
    save_tasks();
    /* Method 2: Go to the first character and set it to null terminator
    for (int i = 0; i < MAX_TASKS; i++)
    {
        tasks[i][0] = '\0';
    }
    num_tasks = 0; */
}

int main(int argc, char *argv[])
{
    load_tasks();

    // If argument is less than 2 - example user just says do, it will print out a guide
    if (argc < 2)
    {
        printf("Usage: do <command> [arguments]\n");
        printf("Commands:\n");
        printf(" add <task>       Add a new task\n");
        printf(" list             List all tasks");
        printf(" remove <index>   Remove a task by its index\n");
        printf(" clear            Clear all tasks\n");
        // Return 1 indicates an error
        return 1;
    }

    // If both strings are the same return 0 meaning success
    if (strcmp(argv[1], "add") == 0)
    {
        if (argc < 3)
        {
            printf("Error: Please enter a task.\n");
        }
        else
        {
            add_task(argv[2]);
        }
    }
    else if (strcmp(argv[1], "list") == 0)
    {
        list_tasks();
    }
    else if (strcmp(argv[1], "remove") == 0)
    {
        if (argc < 3)
        {
            printf("Error: Please enter an index.\n");
        }
        else
        {
            // Convert the task index string into an integer using atoi
            int index = atoi(argv[2]);
            remove_task(index);
        }
    }
    else if (strcmp(argv[2], "clear") == 0)
    {
        clear_tasks();
    }
    else
    {
        printf("Unkown command: %s\n", argv[1]);
    }

    return 0;
}