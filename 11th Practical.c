#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    char name[50];
    char className[20];
    int rollNo;
    float fees;
    float dues;
    float total;
    float advance;
};

struct Teacher {
    char name[50];
    int employeeID;
    float salary;
};

struct Record {
    struct Date date;
    char accountType;  // 'S' for student, 'T' for teacher
    union {
        struct Student student;
        struct Teacher teacher;
    } account;
};

struct Record records[100];
int recordCount = 0;

// Function to add a new record
void addRecord() {
    printf("Enter current date (day month year): ");
    scanf("%d %d %d", &records[recordCount].date.day, &records[recordCount].date.month, &records[recordCount].date.year);

    printf("Enter account type (S for student, T for teacher): ");
    scanf(" %c", &records[recordCount].accountType);

    if (records[recordCount].accountType == 'S') {
        printf("Enter student name: ");
        scanf("%s", records[recordCount].account.student.name);
        printf("Enter class name: ");
        scanf("%s", records[recordCount].account.student.className);
        printf("Enter student roll number: ");
        scanf("%d", &records[recordCount].account.student.rollNo);
        printf("Enter fees: ");
        scanf("%f", &records[recordCount].account.student.fees);
        printf("Enter dues: ");
        scanf("%f", &records[recordCount].account.student.dues);
        printf("Enter total: ");
        scanf("%f", &records[recordCount].account.student.total);
        printf("Enter advance: ");
        scanf("%f", &records[recordCount].account.student.advance);
    } else if (records[recordCount].accountType == 'T') {
        printf("Enter teacher name: ");
        scanf("%s", records[recordCount].account.teacher.name);
        printf("Enter employee ID: ");
        scanf("%d", &records[recordCount].account.teacher.employeeID);
        printf("Enter salary: ");
        scanf("%f", &records[recordCount].account.teacher.salary);
    }

    recordCount++;
    printf("Record added successfully!\n");
}

// Function to display all records
void displayRecords() {
    printf("Date\t\tAccount Type\tName\t\tRoll No/Employee ID\tAmount\n");

    for (int i = 0; i < recordCount; i++) {
        printf("%02d/%02d/%04d\t%c\t\t", records[i].date.day, records[i].date.month, records[i].date.year,
               records[i].accountType);

        if (records[i].accountType == 'S') {
            printf("%s\t\t%d\t\t", records[i].account.student.name, records[i].account.student.rollNo);
            printf("Fees: %.2f, Dues: %.2f, Total: %.2f, Advance: %.2f\n",
                   records[i].account.student.fees, records[i].account.student.dues,
                   records[i].account.student.total, records[i].account.student.advance);
        } else if (records[i].accountType == 'T') {
            printf("%s\t\t%d\t\t", records[i].account.teacher.name, records[i].account.teacher.employeeID);
            printf("Salary: %.2f\n", records[i].account.teacher.salary);
        }
    }
}

// Function to search for a record by roll number or employee ID
void searchRecord() {
    int id;
    printf("Enter Roll No/Employee ID to search: ");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < recordCount; i++) {
        if ((records[i].accountType == 'S' && records[i].account.student.rollNo == id) ||
            (records[i].accountType == 'T' && records[i].account.teacher.employeeID == id)) {
            found = 1;
            printf("Record found:\n");
            printf("Date\t\tAccount Type\tName\t\tRoll No/Employee ID\tAmount\n");
            printf("%02d/%02d/%04d\t%c\t\t", records[i].date.day, records[i].date.month, records[i].date.year,
                   records[i].accountType);

            if (records[i].accountType == 'S') {
                printf("%s\t\t%d\t\t", records[i].account.student.name, records[i].account.student.rollNo);
                printf("Fees: %.2f, Dues: %.2f, Total: %.2f, Advance: %.2f\n",
                       records[i].account.student.fees, records[i].account.student.dues,
                       records[i].account.student.total, records[i].account.student.advance);
            } else if (records[i].accountType == 'T') {
                printf("%s\t\t%d\t\t", records[i].account.teacher.name, records[i].account.teacher.employeeID);
                printf("Salary: %.2f\n", records[i].account.teacher.salary);
            }

            break;
        }
    }

    if (!found) {
        printf("Record not found for Roll No/Employee ID: %d\n", id);
    }
}

// Function to modify a record by roll number or employee ID
void modifyRecord() {
    int id;
    printf("Enter Roll No/Employee ID to modify: ");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < recordCount; i++) {
        if ((records[i].accountType == 'S' && records[i].account.student.rollNo == id) ||
            (records[i].accountType == 'T' && records[i].account.teacher.employeeID == id)) {
            found = 1;

            printf("Enter new data:\n");

            if (records[i].accountType == 'S') {
                printf("Enter student name: ");
                scanf("%s", records[i].account.student.name);
                printf("Enter class name: ");
                scanf("%s", records[i].account.student.className);
                printf("Enter student roll number: ");
                scanf("%d", &records[i].account.student.rollNo);
                printf("Enter fees: ");
                scanf("%f", &records[i].account.student.fees);
                printf("Enter dues: ");
                scanf("%f", &records[i].account.student.dues);
                printf("Enter total: ");
                scanf("%f", &records[i].account.student.total);
                printf("Enter advance: ");
                scanf("%f", &records[i].account.student.advance);
            } else if (records[i].accountType == 'T') {
                printf("Enter teacher name: ");
                scanf("%s", records[i].account.teacher.name);
                printf("Enter employee ID: ");
                scanf("%d", &records[i].account.teacher.employeeID);
                printf("Enter salary: ");
                scanf("%f", &records[i].account.teacher.salary);
            }

            printf("Record modified successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Record not found for Roll No/Employee ID: %d\n", id);
    }
}

// Function to delete a record by roll number or employee ID
void deleteRecord() {
    int id;
    printf("Enter Roll No/Employee ID to delete: ");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < recordCount; i++) {
        if ((records[i].accountType == 'S' && records[i].account.student.rollNo == id) ||
            (records[i].accountType == 'T' && records[i].account.teacher.employeeID == id)) {
            found = 1;

            for (int j = i; j < recordCount - 1; j++) {
                records[j] = records[j + 1];
            }

            recordCount--;

            printf("Record deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Record not found for Roll No/Employee ID: %d\n", id);
    }
}

int main() {
    int choice;

    do {
        printf("\nSchool Billing System\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Search Record\n");
        printf("4. Modify Record\n");
        printf("5. Delete Record\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                searchRecord();
                break;
            case 4:
                modifyRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 0);

    return 0;
}
