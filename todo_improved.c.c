#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TASK_LENGTH 100
#define DEADLINE_LENGTH 20
#define PRIORITY_LENGTH 10

typedef struct {
    char tasks[MAX_TASKS][TASK_LENGTH];
    char deadlines[MAX_TASKS][DEADLINE_LENGTH];
    char priorities[MAX_TASKS][PRIORITY_LENGTH];
    int count;
} ToDoList;

void addTask(ToDoList *list) {
    if (list->count < MAX_TASKS) {
        printf("Enter the task: ");
        getchar();  // To consume any unwanted newline character
        fgets(list->tasks[list->count], TASK_LENGTH, stdin);
        list->tasks[list->count][strcspn(list->tasks[list->count], "\n")] = 0; // Remove newline

        printf("Enter the deadline (YYYY-MM-DD): ");
        fgets(list->deadlines[list->count], DEADLINE_LENGTH, stdin);
        list->deadlines[list->count][strcspn(list->deadlines[list->count], "\n")] = 0; // Remove newline
        
        printf("Enter the priority (High/Medium/Low): ");
        fgets(list->priorities[list->count], PRIORITY_LENGTH, stdin);
        list->priorities[list->count][strcspn(list->priorities[list->count], "\n")] = 0; // Remove newline
        
        list->count++;
        printf("Task added!\n");
    } else {
        printf("Task list is full!\n");
    }
}

void displayTasks(ToDoList *list) {
    if (list->count == 0) {
        printf("No tasks in the list.\n");
    } else {
        printf("\nTask List:\n");
        for (int i = 0; i < list->count; i++) {
            printf("%d. %s (Deadline: %s, Priority: %s)\n", 
                i + 1, list->tasks[i], list->deadlines[i], list->priorities[i]);
        }
    }
}

void removeTask(ToDoList *list) {
    int taskNumber;
    displayTasks(list);
    printf("Enter the task number to remove: ");
    scanf("%d", &taskNumber);
    
    if (taskNumber > 0 && taskNumber <= list->count) {
        for (int i = taskNumber - 1; i < list->count - 1; i++) {
            strcpy(list->tasks[i], list->tasks[i + 1]);
            strcpy(list->deadlines[i], list->deadlines[i + 1]);
            strcpy(list->priorities[i], list->priorities[i + 1]);
        }
        list->count--;
        printf("Task removed!\n");
    } else {
        printf("Invalid task number!\n");
    }
}

void modifyTask(ToDoList *list) {
    int taskNumber;
    displayTasks(list);
    printf("Enter the task number to modify: ");
    scanf("%d", &taskNumber);
    
    if (taskNumber > 0 && taskNumber <= list->count) {
        printf("Enter the new task: ");
        getchar();  // To consume any unwanted newline character
        fgets(list->tasks[taskNumber - 1], TASK_LENGTH, stdin);
        list->tasks[taskNumber - 1][strcspn(list->tasks[taskNumber - 1], "\n")] = 0; // Remove newline

        printf("Enter the new deadline (YYYY-MM-DD): ");
        fgets(list->deadlines[taskNumber - 1], DEADLINE_LENGTH, stdin);
        list->deadlines[taskNumber - 1][strcspn(list->deadlines[taskNumber - 1], "\n")] = 0; // Remove newline
        
        printf("Enter the new priority (High/Medium/Low): ");
        fgets(list->priorities[taskNumber - 1], PRIORITY_LENGTH, stdin);
        list->priorities[taskNumber - 1][strcspn(list->priorities[taskNumber - 1], "\n")] = 0; // Remove newline
        
        printf("Task modified!\n");
    } else {
        printf("Invalid task number!\n");
    }
}

void saveTasksToFile(ToDoList *list) {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < list->count; i++) {
        fprintf(file, "%s|%s|%s\n", list->tasks[i], list->deadlines[i], list->priorities[i]);
    }

    fclose(file);
    printf("Tasks saved to file.\n");
}

void loadTasksFromFile(ToDoList *list) {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("No previous tasks found.\n");
        return;
    }

    while (fscanf(file, "%[^|]|%[^|]|%[^|\n]\n", list->tasks[list->count], 
           list->deadlines[list->count], list->priorities[list->count]) != EOF) {
        list->count++;
    }

    fclose(file);
    printf("Tasks loaded from file.\n");
}

int main() {
    ToDoList list;
    list.count = 0;
    loadTasksFromFile(&list);
    
    int choice;

    do {
        printf("\n--- To-Do List ---\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Remove Task\n");
        printf("4. Modify Task\n");
        printf("5. Save Tasks to File\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(&list);
                break;
            case 2:
                displayTasks(&list);
                break;
            case 3:
                removeTask(&list);
                break;
            case 4:
                modifyTask(&list);
                break;
            case 5:
                saveTasksToFile(&list);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
