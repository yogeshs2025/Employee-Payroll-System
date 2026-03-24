#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Employee {
    int id;
    char name[50];
    float basic;
    int ot_hours;
    float gross;
    float tax;
    float net;
};

struct Employee emp[MAX];
int count = 0;

// Function to calculate salary
void calculate(struct Employee *e) {
    float ot_rate = 100;

    e->gross = e->basic + (e->ot_hours * ot_rate);

    // Tax slab
    if (e->gross > 50000)
        e->tax = e->gross * 0.20;
    else if (e->gross > 30000)
        e->tax = e->gross * 0.10;
    else
        e->tax = 0;

    e->net = e->gross - e->tax;
}

// Add employee
void addEmployee() {
    struct Employee e;

    printf("Enter ID: ");
    fflush(stdout);
    scanf("%d", &e.id);

    printf("Enter Name: ");
    fflush(stdout);
    scanf(" %[^\n]", e.name);

    printf("Enter Basic Pay: ");
    fflush(stdout);
    scanf("%f", &e.basic);

    printf("Enter OT Hours: ");
    fflush(stdout);
    scanf("%d", &e.ot_hours);

    calculate(&e);

    emp[count++] = e;

    printf("Employee Added Successfully!\n");
    fflush(stdout);
}

// Display all employees
void displayAll() {
    if (count == 0) {
        printf("No records found!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\nName: %s\nGross: %.2f\nNet: %.2f\n",
               emp[i].id, emp[i].name, emp[i].gross, emp[i].net);
    }
    fflush(stdout);
}

// Generate payslip
void payslip() {
    int id, found = 0;

    printf("Enter Employee ID: ");
    fflush(stdout);
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (emp[i].id == id) {
            printf("\n===== PAYSLIP =====\n");
            printf("ID: %d\n", emp[i].id);
            printf("Name: %s\n", emp[i].name);
            printf("Basic Pay: %.2f\n", emp[i].basic);
            printf("OT Hours: %d\n", emp[i].ot_hours);
            printf("Gross Pay: %.2f\n", emp[i].gross);
            printf("Tax: %.2f\n", emp[i].tax);
            printf("Net Pay: %.2f\n", emp[i].net);
            printf("===================\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee not found!\n");

    fflush(stdout);
}

// Save to file
void saveToFile() {
    FILE *fp = fopen("payroll.txt", "w");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %f %d %f %f %f\n",
                emp[i].id, emp[i].name, emp[i].basic,
                emp[i].ot_hours, emp[i].gross,
                emp[i].tax, emp[i].net);
    }

    fclose(fp);
    printf("Data saved to file!\n");
    fflush(stdout);
}

// Load from file
void loadFromFile() {
    FILE *fp = fopen("payroll.txt", "r");

    if (fp == NULL) {
        printf("No file found!\n");
        return;
    }

    count = 0;

    while (fscanf(fp, "%d %s %f %d %f %f %f",
                  &emp[count].id,
                  emp[count].name,
                  &emp[count].basic,
                  &emp[count].ot_hours,
                  &emp[count].gross,
                  &emp[count].tax,
                  &emp[count].net) != EOF) {
        count++;
    }

    fclose(fp);
    printf("Data loaded successfully!\n");
    fflush(stdout);
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("\n=== Employee Payroll System ===\n");
        printf("1. Add Employee\n");
        printf("2. Display All\n");
        printf("3. Generate Payslip\n");
        printf("4. Save to File\n");
        printf("5. Load from File\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            fflush(stdout);
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayAll(); break;
            case 3: payslip(); break;
            case 4: saveToFile(); break;
            case 5: loadFromFile(); break;
            case 6:
                printf("Exiting...\n");
                fflush(stdout);
                exit(0);
            default:
                printf("Invalid choice!\n");
                fflush(stdout);
        }
    }

    return 0;
}