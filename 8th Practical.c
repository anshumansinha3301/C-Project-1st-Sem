#include <stdio.h>
#include <stdlib.h>
struct Customer {
char name[50];
long long int phoneNumber;
float amountPaid;};
void addRecord();
void viewRecords();
void searchRecord();
void modifyRecord();
void deleteRecord();
int main() {
    int choice;

    do {
    printf("\n===== Telecom Billing System =====\n");
    printf("1. Add Record\n");
    printf("2. View Records\n");
    printf("3. Search Record\n");
        printf("4. Modify Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                viewRecords();
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
            case 6:
                printf("Exiting the program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 6);

    return 0;
}

void addRecord() {
    FILE *file = fopen("billing_records.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Customer newCustomer;

    printf("Enter Name: ");
    scanf("%s", newCustomer.name);

    printf("Enter Phone Number: ");
    scanf("%ld", &newCustomer.phoneNumber);

    printf("Enter Amount Paid: ");
    scanf("%f", &newCustomer.amountPaid);

    fprintf(file, "%s %lld %.2f\n", newCustomer.name, newCustomer.phoneNumber, newCustomer.amountPaid);

    fclose(file);

    printf("Record added successfully!\n");
}

void viewRecords() {
    FILE *file = fopen("billing_records.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Customer customer;

    printf("\n===== Billing Records =====\n");
    while (fscanf(file, "%s %lld %f", customer.name, &customer.phoneNumber, &customer.amountPaid) != EOF) {
        printf("Name: %s, Phone Number: %lld, Amount Paid: %.2f\n", customer.name, customer.phoneNumber, customer.amountPaid);
    }

    fclose(file);
}

void searchRecord() {
    long long int targetPhoneNumber;
    printf("Enter the Phone Number to search: ");
    scanf("%lld", &targetPhoneNumber);

    FILE *file = fopen("billing_records.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Customer customer;
    int found = 0;

    while (fscanf(file, "%s %lld %f", customer.name, &customer.phoneNumber, &customer.amountPaid) != EOF) {
        if (customer.phoneNumber == targetPhoneNumber) {
            printf("\n===== Record Found =====\n");
            printf("Name: %s, Phone Number: %lld, Amount Paid: %.2f\n", customer.name, customer.phoneNumber, customer.amountPaid);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Record not found.\n");
    }
}

void modifyRecord() {
    long long int targetPhoneNumber;
    printf("Enter the Phone Number to modify: ");
    scanf("%lld", &targetPhoneNumber);

    FILE *file = fopen("billing_records.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Customer customer;
    int found = 0;

    FILE *tempFile = fopen("temp.txt", "w");
    while (fscanf(file, "%s %lld %f", customer.name, &customer.phoneNumber, &customer.amountPaid) != EOF) {
        if (customer.phoneNumber == targetPhoneNumber) {
            printf("Enter new name for the customer: ");
            scanf("%s", customer.name);

            printf("Enter new amount paid for the customer: ");
            scanf("%f", &customer.amountPaid);

            found = 1;
        }
        fprintf(tempFile, "%s %lld %.2f\n", customer.name, customer.phoneNumber, customer.amountPaid);
    }

    fclose(file);
    fclose(tempFile);

    remove("billing_records.txt");
    rename("temp.txt", "billing_records.txt");

    if (found) {
        printf("Record modified successfully!\n");
    } else {
        printf("Record not found.\n");
    }
}

void deleteRecord() {
    long long int targetPhoneNumber;
    printf("Enter the Phone Number to delete: ");
    scanf("%lld", &targetPhoneNumber);

    FILE *file = fopen("billing_records.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Customer customer;
    int found = 0;

    FILE *tempFile = fopen("temp.txt", "w");
    while (fscanf(file, "%s %lld %f", customer.name, &customer.phoneNumber, &customer.amountPaid) != EOF) {
        if (customer.phoneNumber == targetPhoneNumber) {
            found = 1;
        } else {
            fprintf(tempFile, "%s %lld %.2f\n", customer.name, customer.phoneNumber, customer.amountPaid);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("billing_records.txt");
    rename("temp.txt", "billing_records.txt");

    if (found) {
        printf("Record deleted successfully!\n");
    } else {
        printf("Record not found.\n");
    }
}
