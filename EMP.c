#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Employee structure
typedef struct Employee
{
    char name[50];
    char designation[50];
    float basicPay;
    struct Employee *next;
} Employee;

// Function Prototypes
void requirements(Employee *employee);
int genMORY();
void monthORyear(int, float);
int AnotherCatg(Employee *employee);
float empda(float);
float empta(float);
float emphpl(float);
float emppf(float);
float empbonus(float);
float emptax(float);
void addEmployee(Employee **head, char name[], char designation[], float bsp);
void displayEmployee(Employee *employee);
void freeEmployees(Employee *head);

int main() {
    printf("EMPLOYEE MANAGEMENT SYSTEM\n");
    int x = 1;
    float bsp;
    char name[50], designation[50];
    Employee *head = NULL;

    while (x == 1) {
        printf("\nEnter Employee Name: ");
        scanf(" %[^\n]", name);
        printf("Enter Employee Designation: ");
        scanf(" %[^\n]", designation);
        printf("Enter the Basic Pay of the Employee for a month: ");
        scanf("%f", &bsp);

        addEmployee(&head, name, designation, bsp);
        requirements(head);

        while (AnotherCatg(head)) {
            // Loop until user exits category selection
        }

        printf("\nDo you want to calculate salary of another employee? If 'yes', enter (1); else enter (0) to EXIT.\n:");
        scanf("%d", &x);
    }

    freeEmployees(head);
    printf("\nExiting Employee Management System...\n");
    return 0;
}

// Add employee to linked list
void addEmployee(Employee **head, char name[], char designation[], float bsp) {
    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));
    strcpy(newEmployee->name, name);
    strcpy(newEmployee->designation, designation);
    newEmployee->basicPay = bsp;
    newEmployee->next = *head;
    *head = newEmployee;
}

// Display employee details
void displayEmployee(Employee *employee) {
    printf("\nEmployee Name: %s", employee->name);
    printf("\nEmployee Designation: %s", employee->designation);
}

// Salary component functions
float empda(float bsp) { return 0.35 * bsp; }
float empta(float bsp) { return 0.15 * bsp; }
float emphpl(float bsp) {
    float lv, deduction = 0;
    printf("Enter number of leaves taken: ");
    scanf("%f", &lv);
    deduction = (lv > 3) ? (lv - 3) * (bsp / 30) : 0;
    return deduction;
}
float emppf(float bsp) { return 0.15 * bsp; }
float empbonus(float bsp) { return 0.1 * bsp; }
float emptax(float bsp) { return 0.07 * bsp; }

// Monthly or yearly display
void monthORyear(int choice, float amount) {
    char K;
    if (choice == 0) {
        printf("Monthly : %.2f\n", amount);
        printf("Want to Check for Yearly? [Y/N]\n:");
        scanf(" %c", &K);
        if (K == 'Y' || K == 'y') {
            printf("Yearly : %.2f\n", amount * 12);
        }
    } else if (choice == 1) {
        printf("Yearly : %.2f\n", amount * 12);
        printf("Want to Check for Monthly? [Y/N]\n:");
        scanf(" %c", &K);
        if (K == 'Y' || K == 'y') {
            printf("Monthly : %.2f\n", amount);
        }
    } else {
        printf("Invalid choice! Please retry.\n");
    }
}

// Get monthly/yearly choice
int genMORY() {
    int choice;
    do {
        printf("\nFor Monthly enter-(0) OR for Yearly enter-(1)\n:");
        scanf("%d", &choice);
        if (choice != 0 && choice != 1) {
            printf("Invalid input. Try again.\n");
        }
    } while (choice != 0 && choice != 1);
    return choice;
}

// Handle salary requirements
void requirements(Employee *employee) {
    int val;
    float a, b, c, d, e, f, g, z;

    while (1) {
        printf("\nChoose a requirement:\n");
        printf("1. Dearness Allowance\n2. Travel Allowance\n3. Pay-cut Leaves\n");
        printf("4. Provident Fund\n5. Bonus\n6. Tax\n7. Total salary\n8. Exit\n:");
        scanf("%d", &val);

        switch (val) {
            case 1:
                a = empda(employee->basicPay);
                displayEmployee(employee);
                printf("\nDearness Allowance:\n");
                monthORyear(genMORY(), a);
                return;
            case 2:
                b = empta(employee->basicPay);
                displayEmployee(employee);
                printf("\nTravel Allowance:\n");
                monthORyear(genMORY(), b);
                return;
            case 3:
                c = emphpl(employee->basicPay);
                displayEmployee(employee);
                printf("\nPay-cut Leaves Deduction: %.2f\n", c);
                return;
            case 4:
                d = emppf(employee->basicPay);
                displayEmployee(employee);
                printf("\nProvident Fund:\n");
                monthORyear(genMORY(), d);
                return;
            case 5:
                f = empbonus(employee->basicPay);
                displayEmployee(employee);
                printf("\nBonus:\n");
                monthORyear(genMORY(), f);
                return;
            case 6:
                g = emptax(employee->basicPay);
                displayEmployee(employee);
                printf("\nTax:\n");
                monthORyear(genMORY(), g);
                return;
            case 7:
                e = employee->basicPay + empda(employee->basicPay) + empta(employee->basicPay) + empbonus(employee->basicPay)
                    - emppf(employee->basicPay) - emptax(employee->basicPay);
                z = e - emphpl(employee->basicPay);
                displayEmployee(employee);
                printf("\nTotal Salary:\n");
                monthORyear(genMORY(), z);
                return;
            case 8:
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

// Check additional category
int AnotherCatg(Employee *employee) {
    char sel;
    printf("\nWant to check another category for the user? [Y/N]\n:");
    scanf(" %c", &sel);

    if (sel == 'Y' || sel == 'y') {
        requirements(employee);
        return 1;
    } else if (sel == 'N' || sel == 'n') {
        printf("\nExiting category selection for this user.\n");
        return 0;
    } else {
        printf("Invalid input! Please enter 'Y' or 'N'.\n");
        return AnotherCatg(employee);
    }
}

// Free memory
void freeEmployees(Employee *head) {
    Employee *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}