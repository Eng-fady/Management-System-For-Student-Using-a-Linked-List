#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000

// Define the structure for student data
struct student {
    int id;
    char name[100];
    int age;
    float gpa;
    struct student *next;
};

// Function prototypes
void addStudent(struct student **head);
void displayStudents(struct student *head);
void searchStudentByID(struct student *head, int id);
void updateStudent(struct student *head, int id);
void deleteStudent(struct student **head, int id);
float calculateAverageGPA(struct student *head);
void searchHighestGPA(struct student *head);

// Main function
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);	// Set the buffering mode of stdout to unbuffered
	setvbuf(stderr, NULL, _IONBF, 0);	// Set the buffering mode of stderr to unbuffered

    struct student *head = NULL;
    int choice, id;

    while (1) {
        printf("\n\t\t**Menu Options**\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("1. Add a Student\n");
        printf("2. Display All Students\n");
        printf("3. Search for a Student by ID\n");
        printf("4. Update Student Information\n");
        printf("5. Delete a Student\n");
        printf("6. Calculate Average GPA\n");
        printf("7. Find Student with Highest GPA\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("-----------------------------------------------------------------------------\n");

        switch (choice) {
            case 1:
                addStudent(&head);
                break;
            case 2:
                displayStudents(head);
                break;
            case 3:
                printf("Enter student ID to search: ");
                scanf("%d", &id);
                searchStudentByID(head, id);
                break;
            case 4:
                printf("Enter student ID to update: ");
                scanf("%d", &id);
                updateStudent(head, id);
                break;
            case 5:
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(&head, id);
                break;
            case 6:
                printf("Average GPA: %.3f\n", calculateAverageGPA(head));
                break;
            case 7:
                searchHighestGPA(head);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add a student to the linked list
void addStudent(struct student **head) {
    int id;
    printf("Enter student ID: ");
    scanf("%d", &id);

    struct student *current = *head;
    while (current) {
        if (current->id == id) {
            printf("ID is already taken.\n");
            return;
        }
        current = current->next;
    }

    struct student *newStudent = (struct student *)malloc(sizeof(struct student));
    if (!newStudent) {
        printf("Memory allocation failed.\n");
        return;
    }

    newStudent->id = id;
    getchar(); // to consume the newline character left by scanf
    printf("Enter student name: ");
    fgets(newStudent->name, 100, stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0'; // Remove trailing newline character
    printf("Enter student age: ");
    scanf("%d", &newStudent->age);
    printf("Enter student GPA: ");
    scanf("%f", &newStudent->gpa);

    newStudent->next = *head;
    *head = newStudent;

    printf("Student added successfully.\n");
}

// Function to display all students in the linked list
void displayStudents(struct student *head) {
    if (!head) {
        printf("No students to display.\n");
        return;
    }

    struct student *current = head;
    struct student *stack[MAX_SIZE];  // Assuming a maximum of 1000 students
    int top = -1;

    while (current) {
        stack[++top] = current;
        current = current->next;
    }

    while (top >= 0) {
        current = stack[top--];
        printf("ID: %d, Name: %s, Age: %d, GPA: %.3f\n",
               current->id, current->name, current->age, current->gpa);
    }
}

// Function to search for a student by ID
void searchStudentByID(struct student *head, int id) {
    struct student *current = head;
    while (current) {
        if (current->id == id) {
            printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
                   current->id, current->name, current->age, current->gpa);
            return;
        }
        current = current->next;
    }
    printf("Student not found.\n");
}

// Function to update student information
void updateStudent(struct student *head, int id) {
    struct student *current = head;
    while (current) {
        if (current->id == id) {
            getchar(); // to consume the newline character left by scanf
            printf("Enter new name: ");
            fgets(current->name, 100, stdin);
            current->name[strcspn(current->name, "\n")] = '\0'; // Remove trailing newline character
            printf("Enter new age: ");
            scanf("%d", &current->age);
            printf("Enter new GPA: ");
            scanf("%f", &current->gpa);
            printf("Student updated successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Student not found.\n");
}

// Function to delete a student by ID
void deleteStudent(struct student **head, int id) {
    struct student *current = *head, *prev = NULL;

    while (current && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        printf("Student not found.\n");
        return;
    }

    if (prev) {
        prev->next = current->next;
    } else {
        *head = current->next;
    }

    free(current);
    printf("Student deleted successfully.\n");
}

// Function to calculate the average GPA of all students
float calculateAverageGPA(struct student *head) {
    if (!head) return 0.0;

    int count = 0;
    float totalGPA = 0.0;
    struct student *current = head;

    while (current) {
        totalGPA += current->gpa;
        count++;
        current = current->next;
    }

    return (count == 0) ? 0.0 : (totalGPA / count);
}

// Function to find the student with the highest GPA
void searchHighestGPA(struct student *head) {
    if (!head) {
        printf("No students to search.\n");
        return;
    }

    struct student *current = head;
    struct student *highest = head;

    while (current) {
        if (current->gpa > highest->gpa) {
            highest = current;
        }
        current = current->next;
    }

    printf("Student with highest GPA:\n");
    printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
           highest->id, highest->name, highest->age, highest->gpa);
}
