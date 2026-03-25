#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define OT_RATE 100

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

// ---------- UTILITY ----------

void clearBuffer() {
    while (getchar() != '\n');
}

int inputInt(const char *msg) {
    int value;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &value) == 1)
            return value;
        else {
            printf("⚠ Invalid input! Enter a number.\n");
            clearBuffer();
        }
    }
}

float inputFloat(const char *msg) {
    float value;
    while (1) {
        printf("%s", msg);
        if (scanf("%f", &value) == 1)
            return value;
        else {
            printf("⚠ Invalid input! Enter a valid number.\n");
            clearBuffer();
        }
    }
}

void inputString(const char *msg, char *str) {
    printf("%s", msg);
    scanf(" %[^\n]", str);
}

int isValidName(char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ')
            return 0;
    }
    return strlen(name) > 0;
}

void line() {
    printf("\n-------------------------------------------\n");
}

// ---------- CALCULATION ----------

void calculate(struct Employee *e) {
    e->gross = e->basic + (e->ot_hours * OT_RATE);

    if (e->gross > 50000)
        e->tax = e->gross * 0.20;
    else if (e->gross > 30000)
        e->tax = e->gross * 0.10;
    else
        e->tax = 0;

    e->net = e->gross - e->tax;
}

// ---------- FEATURES ----------

void addEmployee() {
    if (count >= MAX) {
        printf("\n⚠ Employee limit reached!\n");
        return;
    }

    struct Employee e;

    line();
    printf("        ADD NEW EMPLOYEE\n");
    line();

    while (1) {
        int valid = 1;
        e.id = inputInt("Enter Employee ID   : ");

        if (e.id <= 0) {
            printf("⚠ ID must be positive!\n");
            continue;
        }

        for (int i = 0; i < count; i++) {
            if (emp[i].id == e.id) {
                printf("⚠ ID already exists!\n");
                valid = 0;
                break;
            }
        }

        if (valid) break;
    }

    while (1) {
        inputString("Enter Name          : ", e.name);
        if (isValidName(e.name)) break;
        printf("⚠ Name must contain only alphabets and spaces!\n");
    }

    while (1) {
        e.basic = inputFloat("Enter Basic Pay     : ");
        if (e.basic >= 0 && e.basic <= 1000000) break;
        printf("⚠ Invalid salary!\n");
    }

    while (1) {
        e.ot_hours = inputInt("Enter OT Hours      : ");
        if (e.ot_hours >= 0 && e.ot_hours <= 100) break;
        printf("⚠ Invalid OT hours!\n");
    }

    calculate(&e);
    emp[count++] = e;

    printf("\n✔ Employee Added Successfully!\n");
}

void displayAll() {
    if (count == 0) {
        printf("\n⚠ No records found!\n");
        return;
    }

    line();
    printf("         EMPLOYEE LIST\n");
    line();

    for (int i = 0; i < count; i++) {
        printf("ID: %-5d Name: %-15s Net Pay: %.2f\n",
               emp[i].id, emp[i].name, emp[i].net);
    }
}

void generatePayslip() {
    int id = inputInt("\nEnter Employee ID: ");
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (emp[i].id == id) {
            found = 1;

            line();
            printf("           PAYSLIP\n");
            line();

            printf("ID            : %d\n", emp[i].id);
            printf("Name          : %s\n", emp[i].name);
            printf("Basic Pay     : %.2f\n", emp[i].basic);
            printf("OT Hours      : %d\n", emp[i].ot_hours);
            printf("OT Rate       : %d\n", OT_RATE);

            line();

            printf("Gross Pay     : %.2f\n", emp[i].gross);
            printf("Tax Deduction : %.2f\n", emp[i].tax);
            printf("Net Pay       : %.2f\n", emp[i].net);

            line();

            return;
        }
    }

    if (!found)
        printf("\n⚠ Employee not found!\n");
}

void updateEmployee() {
    int id = inputInt("\nEnter Employee ID to update: ");

    for (int i = 0; i < count; i++) {
        if (emp[i].id == id) {

            while (1) {
                inputString("Enter New Name       : ", emp[i].name);
                if (isValidName(emp[i].name)) break;
                printf("⚠ Invalid name!\n");
            }

            while (1) {
                emp[i].basic = inputFloat("Enter New Basic Pay  : ");
                if (emp[i].basic >= 0) break;
                printf("⚠ Invalid salary!\n");
            }

            while (1) {
                emp[i].ot_hours = inputInt("Enter New OT Hours   : ");
                if (emp[i].ot_hours >= 0) break;
                printf("⚠ Invalid OT hours!\n");
            }

            calculate(&emp[i]);

            printf("\n✔ Employee Updated!\n");
            return;
        }
    }

    printf("\n⚠ Employee not found!\n");
}

void deleteEmployee() {
    int id = inputInt("\nEnter Employee ID to delete: ");

    for (int i = 0; i < count; i++) {
        if (emp[i].id == id) {

            for (int j = i; j < count - 1; j++)
                emp[j] = emp[j + 1];

            count--;

            printf("\n✔ Employee Deleted!\n");
            return;
        }
    }

    printf("\n⚠ Employee not found!\n");
}

// ---------- FILE HANDLING (CSV FORMAT) ----------

void saveToFile() {
    FILE *fp = fopen("payroll.csv", "w");

    if (fp == NULL) {
        printf("\n⚠ Error saving file!\n");
        return;
    }

    fprintf(fp, "ID,Name,Basic,OT,Gross,Tax,Net\n");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%.2f,%d,%.2f,%.2f,%.2f\n",
                emp[i].id, emp[i].name, emp[i].basic,
                emp[i].ot_hours, emp[i].gross,
                emp[i].tax, emp[i].net);
    }

    fclose(fp);
    printf("\n✔ Data saved to payroll.csv\n");
}

void loadFromFile() {
    FILE *fp = fopen("payroll.csv", "r");

    if (fp == NULL) return;

    count = 0;
    char linebuf[200];

    fgets(linebuf, sizeof(linebuf), fp); // skip header

    while (fscanf(fp, "%d,%49[^,],%f,%d,%f,%f,%f\n",
                  &emp[count].id,
                  emp[count].name,
                  &emp[count].basic,
                  &emp[count].ot_hours,
                  &emp[count].gross,
                  &emp[count].tax,
                  &emp[count].net) == 7) {
        count++;
    }

    fclose(fp);
}

// ---------- MAIN ----------

int main() {
    loadFromFile();

    int choice;

    while (1) {
        line();
        printf("   EMPLOYEE PAYROLL SYSTEM\n");
        line();

        printf("1. Add Employee\n");
        printf("2. Display All\n");
        printf("3. Payslip\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Save\n");
        printf("7. Exit\n");

        line();
        choice = inputInt("Enter choice: ");

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayAll(); break;
            case 3: generatePayslip(); break;
            case 4: updateEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: saveToFile(); break;
            case 7:
                saveToFile();
                printf("\n👋 Exiting... Data saved!\n");
                exit(0);
            default:
                printf("\n⚠ Invalid choice!\n");
        }
    }
}