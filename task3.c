#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

FILE *fp;

// Function to add a student record
void addStudent() {
    struct Student s;
    fp = fopen("students.dat", "ab"); // append in binary mode
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    getchar(); // to consume newline left by scanf
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove newline
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Record added successfully!\n");
}

// Function to display all students
void displayStudents() {
    struct Student s;
    fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }
    printf("\n---- Student Records ----\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("ID: %d | Name: %s | Age: %d | Marks: %.2f\n", s.id, s.name, s.age, s.marks);
    }
    fclose(fp);
}

// Function to search student by ID
void searchStudent() {
    int id, found = 0;
    struct Student s;
    printf("Enter student ID to search: ");
    scanf("%d", &id);

    fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Record found!\n");
            printf("ID: %d | Name: %s | Age: %d | Marks: %.2f\n", s.id, s.name, s.age, s.marks);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Record not found!\n");
}

// Function to update student record
void updateStudent() {
    int id, found = 0;
    struct Student s;
    FILE *fpTemp;

    printf("Enter student ID to update: ");
    scanf("%d", &id);

    fp = fopen("students.dat", "rb");
    fpTemp = fopen("temp.dat", "wb");

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Enter new Name: ");
            getchar();
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);
            found = 1;
        }
        fwrite(&s, sizeof(s), 1, fpTemp);
    }

    fclose(fp);
    fclose(fpTemp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record updated successfully!\n");
    else
        printf("Record not found!\n");
}

// Function to delete student record
void deleteStudent() {
    int id, found = 0;
    struct Student s;
    FILE *fpTemp;

    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    fp = fopen("students.dat", "rb");
    fpTemp = fopen("temp.dat", "wb");

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;
            continue; // skip writing this record
        }
        fwrite(&s, sizeof(s), 1, fpTemp);
    }

    fclose(fp);
    fclose(fpTemp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("Record not found!\n");
}

int main() {
    int choice;
    do {
        printf("\n===== Student Record Management =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
