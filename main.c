#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define COURSE_LEN 50
#define FILENAME "students.dat"

/* ---------- Structure Definition ---------- */
typedef struct {
    int id;
    char name[NAME_LEN];
    char course[COURSE_LEN];
    float marks;
    int active; /* 1 = active record, 0 = deleted (soft delete) */
} Student;

/* ---------- Global Array of Structures ---------- */
Student students[MAX_STUDENTS];
int studentCount = 0;

/* ---------- Function Prototypes ---------- */
void showMenu(void);
void addStudent(void);
void displayAllStudents(void);
int findStudentIndexById(int id);   
void searchStudentById(void);
void updateStudent(void);
void deleteStudent(void);
void saveToFile(void);
void loadFromFile(void);
void clearInputBuffer(void);
int getValidInt(const char *prompt);
float getValidFloat(const char *prompt);
void getValidString(const char *prompt, char *buffer, int size);

/* ---------- main ---------- */
int main(void) {
    int choice;

    loadFromFile();   /* Load existing data at startup */

    do {
        showMenu();
        choice = getValidInt("Enter your choice: ");

        switch (choice) {
            case 1: addStudent();           break;
            case 2: displayAllStudents();   break;
            case 3: searchStudentById();    break;
            case 4: updateStudent();        break;
            case 5: deleteStudent();        break;
            case 6: saveToFile();           break;
            case 0:
                saveToFile(); /* auto-save before exit */
                printf("\nData saved. Exiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

/* ---------- Menu Display ---------- */
void showMenu(void) {
    printf("\n===================================\n");
    printf("   STUDENT MANAGEMENT SYSTEM\n");
    printf("===================================\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student by ID\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Save to File\n");
    printf("0. Exit\n");
    printf("===================================\n");
}

/* ---------- Input Helpers ---------- */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Please enter a number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

float getValidFloat(const char *prompt) {
    float value;
    printf("%s", prompt);
    while (scanf("%f", &value) != 1) {
        printf("Invalid input. Please enter a number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

void getValidString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    /* remove trailing newline if present */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}
/* ---------- Add Student ---------- */
void addStudent(void) {
    if (studentCount >= MAX_STUDENTS) {
        printf("\nStudent list is full. Cannot add more records.\n");
        return;
    }

    Student s;
    s.id = getValidInt("Enter Student ID: ");

    /* Prevent duplicate IDs among active records */
    if (findStudentIndexById(s.id) != -1) {
        printf("\nA student with ID %d already exists.\n", s.id);
        return;
    }

    getValidString("Enter Student Name: ", s.name, NAME_LEN);
    getValidString("Enter Course: ", s.course, COURSE_LEN);
    s.marks = getValidFloat("Enter Marks: ");
    s.active = 1;

    students[studentCount] = s;
    studentCount++;

    printf("\nStudent added successfully!\n");
}

/* ---------- Display All Students ---------- */
void displayAllStudents(void) {
    int found = 0;

    printf("\n--------------------------------------------------------------\n");
    printf("%-6s %-20s %-20s %-8s\n", "ID", "Name", "Course", "Marks");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        if (students[i].active) {
            printf("%-6d %-20s %-20s %-8.2f\n",
                   students[i].id, students[i].name,
                   students[i].course, students[i].marks);
            found = 1;
        }
    }

    if (!found) {
        printf("No student records found.\n");
    }
    printf("--------------------------------------------------------------\n");
}

/* ---------- Linear Search by ID ---------- */
int findStudentIndexById(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].active && students[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* ---------- Search Student by ID ---------- */
void searchStudentById(void) {
    int id = getValidInt("Enter Student ID to search: ");
    int index = findStudentIndexById(id);

    if (index == -1) {
        printf("\nStudent with ID %d not found.\n", id);
        return;
    }

    printf("\n--- Student Found ---\n");
    printf("ID     : %d\n", students[index].id);
    printf("Name   : %s\n", students[index].name);
    printf("Course : %s\n", students[index].course);
    printf("Marks  : %.2f\n", students[index].marks);
}

/* ---------- Update Student ---------- */
void updateStudent(void) {
    int id = getValidInt("Enter Student ID to update: ");
    int index = findStudentIndexById(id);

    if (index == -1) {
        printf("\nStudent with ID %d not found.\n", id);
        return;
    }

    printf("\nCurrent details:\n");
    printf("Name   : %s\n", students[index].name);
    printf("Course : %s\n", students[index].course);
    printf("Marks  : %.2f\n", students[index].marks);

    printf("\nEnter new details (leave name/course blank to keep current):\n");

    char nameBuf[NAME_LEN];
    char courseBuf[COURSE_LEN];

    getValidString("New Name: ", nameBuf, NAME_LEN);
    if (strlen(nameBuf) > 0) {
        strcpy(students[index].name, nameBuf);
    }

    getValidString("New Course: ", courseBuf, COURSE_LEN);
    if (strlen(courseBuf) > 0) {
        strcpy(students[index].course, courseBuf);
    }

    students[index].marks = getValidFloat("New Marks: ");

    printf("\nStudent record updated successfully!\n");
}

/* ---------- Delete Student ---------- */
void deleteStudent(void) {
    int id = getValidInt("Enter Student ID to delete: ");
    int index = findStudentIndexById(id);

    if (index == -1) {
        printf("\nStudent with ID %d not found.\n", id);
        return;
    }

    char confirm[10];
    getValidString("Are you sure you want to delete this record? (y/n): ", confirm, sizeof(confirm));

    if (confirm[0] == 'y' || confirm[0] == 'Y') {
        /* Shift remaining records left to keep array compact */
        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf("\nStudent record deleted successfully!\n");
    } else {
        printf("\nDelete cancelled.\n");
    }
}

/* ---------- Save to File (binary) ---------- */
void saveToFile(void) {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("\nError: Could not open file for saving.\n");
        return;
    }

    fwrite(&studentCount, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), studentCount, fp);

    fclose(fp);
    printf("\nData saved to '%s' successfully.\n", FILENAME);
}

/* ---------- Load from File (binary) ---------- */
void loadFromFile(void) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        /* No existing file yet - not an error on first run */
        printf("No existing data file found. Starting with an empty list.\n");
        return;
    }

    fread(&studentCount, sizeof(int), 1, fp);
    fread(students, sizeof(Student), studentCount, fp);

    fclose(fp);
    printf("Loaded %d student record(s) from '%s'.\n", studentCount, FILENAME);
}