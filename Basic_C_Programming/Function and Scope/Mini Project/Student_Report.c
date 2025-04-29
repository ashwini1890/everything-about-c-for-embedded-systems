/*
📘 Problem Statement: Student Report Management System (with File Storage & Table Output)
🔍 Objective:

Design and implement a menu-driven C program that simulates a simple student report management system.
The system should allow the user to:

    Input a student’s name, roll number, and marks for 3 subjects.

    Calculate total marks, average, and grade.

    Display the report in a neatly formatted table on the terminal.

    Save the report to a text file (student_report.txt) in the same folder.

    Navigate through options using a looped menu until the user chooses to exit.

📌 Functional Requirements:
1. Menu System (Using switch)

    Option 1: Enter Student Details (name, roll, and 3 subject marks)

    Option 2: View Last Saved Report

    Option 3: Exit the Program

2. Input Validation

    Marks should be in the range of 0 to 100

    Invalid marks prompt the user to re-enter using a while loop and continue

3. Grading Criteria (Using nested if)
        Average (%)	Grade
          90–100	A
           75–89	B
           60–74	C
           40–59	D
        Below 40	F
    
*/

#include <stdio.h>
#include <string.h>

int main() {
    char name[50];
    int roll, marks[3], total;
    float average;
    char grade;
    int choice;
    char repeat;
    int i;

    FILE *reportFile;

menu:
    do {
        printf("\n===== Student Report Management System =====\n");
        printf("1. Enter Student Details\n");
        printf("2. View Last Report\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: // To Enter Student Details 
            
                printf("\n====Report Card Generation Form====\n\n");    
                printf("\nEnter student name: ");
                scanf(" %[^\n]", name);
                printf("Enter roll number: ");
                scanf("%d", &roll);

                total = 0;

                for (i = 0; i < 3; i++) {
                    while (1) {                        
                        printf("Enter marks for Subject %d (0-100): ", i + 1);
                        scanf("%d", &marks[i]);
                        if (marks[i] < 0 || marks[i] > 100) {
                            printf("Invalid marks! Try again.\n");
                            continue;
                        }
                        break;
                    }
                    total +=marks[i];
                }

                average = total / 3.0;

                if (average >= 90)
                    grade = 'A';
                else if (average >= 75)
                    grade = 'B';
                else if (average >= 60)
                    grade = 'C';
                else if (average >= 40)
                    grade = 'D';
                else
                    grade = 'F';

                printf("\nStudent record saved successfully!\n");
                break;

            case 2: // View the Data of the Student & save it in a file
                if (strlen(name) == 0) {
                    printf("\nNo report found! Please enter student details first.\n");
                    goto menu;
                }

                // Open file for writing
                reportFile = fopen("student_report.txt", "w");
                if (reportFile == NULL) {
                    printf("Error opening file for writing!\n");
                    return 1;
                }

                printf("\n======= Student Report =======\n");
                fprintf(reportFile, "======= Student Report =======\n");

                printf("Name       : %s\n", name);
                fprintf(reportFile, "Name       : %s\n", name);

                printf("Roll No.   : %d\n", roll);
                fprintf(reportFile, "Roll No.   : %d\n", roll);

                printf("+-----------+--------+\n");
                printf("| Subject   | Marks  |\n");
                printf("+-----------+--------+\n");

                fprintf(reportFile, "+-----------+--------+\n");
                fprintf(reportFile, "| Subject   | Marks  |\n");
                fprintf(reportFile, "+-----------+--------+\n");

                for (i = 0; i < 3; i++) {
                    printf("| Subject %d |  %3d   |\n", i + 1, marks[i]);
                    fprintf(reportFile, "| Subject %d |  %3d   |\n", i + 1, marks[i]);
                }

                printf("+-----------+--------+\n");
                fprintf(reportFile, "+-----------+--------+\n");

                printf("Total Marks: %d\n", total);
                printf("Average    : %.2f\n", average);
                printf("Grade      : %c\n", grade);

                fprintf(reportFile, "Total Marks: %d\n", total);
                fprintf(reportFile, "Average    : %.2f\n", average);
                fprintf(reportFile, "Grade      : %c\n", grade);

                if (grade == 'A')
                    fprintf(reportFile, "Remarks    : Excellent\n");
                else if (grade == 'B')
                    fprintf(reportFile, "Remarks    : Very Good\n");
                else if (grade == 'C')
                    fprintf(reportFile, "Remarks    : Good\n");
                else if (grade == 'D')
                    fprintf(reportFile, "Remarks    : Pass\n");
                else
                    fprintf(reportFile, "Remarks    : Fail. Need improvement.\n");

                fclose(reportFile);
                printf("\nReport saved to 'student_report.txt'.\n");
                break;

            case 3: //EXIT the Code
                printf("Exiting program. Thank you!\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }

        printf("\nDo you want to go back to the main menu? (y/n): ");
        scanf(" %c", &repeat);

    } while (repeat == 'y' || repeat == 'Y');

    printf("Program terminated.\n");
    return 0;
}
