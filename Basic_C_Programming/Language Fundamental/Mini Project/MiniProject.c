/*-----*****Mini Project: Student Report Card Generator*****---------*/

/* 📝 Project Statement: ----------------
    Create a C program that acts as a Student Report Card Generator for a single student.
    The program should:

    Take inputs for:

        Student Name, Roll Number

        Marks in 5 subjects (out of 100)

    Calculate:

        Total Marks

        Percentage (use type casting)

        Grade based on the percentage

    Display a well-formatted report card on screen.

💡 Grading Criteria:

    A+ – ≥ 90%

    A – 80–89%

    B – 70–79%

    C – 60–69%

    D – 40–59%

    F – < 40%

✅ File Output – Save the report to report.txt using fprintf()

✅ Pass/Fail Status + Motivational Remarks based on performance

⚙️ Features You’ll Use:
Concept     	    Where It's Applied
Tokens	            Entire program structure
Keywords	        int, float, if, else, return, etc.
Identifiers	        rollNo, total, percentage, grade, etc.
Data Types	        int, float, char[], unsigned int
Modifiers	        Use unsigned int for marks
I/O Functions   	scanf() and printf()
Type Casting	    percentage = (float)total / 5;
Write to file	    fopen(), fprintf(), fclose()
Conditional logic	if...else for remarks
File safety check	if (file == NULL)
Remarks	            Custom motivational messages
*/

#include<stdio.h>
#include <string.h>

#define S_Name_MAX_LENGTH 100         //macro to define length of the array of charactor (string)

char Name[S_Name_MAX_LENGTH];
int RollNo;
unsigned int marks1, marks2, marks3, marks4, marks5;
float total, percentage;
char  grade[3];         //array of size 3bytes
char remark[50];
char status[10];

int main(){

    FILE *file; // file pointer
    file = fopen("report.txt", "w");  // Open file in write mode, w is use to write 
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter Student's Name: ");
    getchar();  // Flush newline from previous scanf 
    fgets(Name, S_Name_MAX_LENGTH, stdin);   //fgets read entire line with space, stdin = Read from Keyboad
    Name[strcspn(Name, "\n")] = 0;  // Remove newline

    printf("Enter Roll Number: ");
    scanf("%d", &RollNo);

    printf("Enter marks in 5 subjects (out of 100):\n");
    printf("Maths: ");
    scanf("%u",&marks1);
    printf("Physics: ");
    scanf("%u",&marks2);
    printf("Chemistry: ");
    scanf("%u",&marks3);
    printf("English: ");
    scanf("%u",&marks4);
    printf("Computer: ");
    scanf("%u",&marks5);

// Calculation for Grade: 

total = ((float)(marks1 + marks2 + marks3 + marks4 + marks5));       //type casting int -> float
percentage = (total*100)/500;

if(percentage>=90)              // You cannot assign arrays using =  
    strcpy(grade, "A+");       //strcpy() copies the characters from one string into your array
else if (percentage >= 80)
    strcpy(grade, "A");
else if (percentage >= 70)
    strcpy(grade, "B");
else if (percentage >= 60)
    strcpy(grade, "C");
else if (percentage >= 40)
    strcpy(grade, "D");
else
    strcpy(grade, "F");

// Pass/Fail and Remarks
if (percentage >= 40) {
    strcpy(status, "Pass");
    if (percentage >= 90)
    strcpy(remark, "Excellent! Keep it up!");
    else if (percentage >= 75)
    strcpy(remark, "Very Good! Aim for the top!");
    else if (percentage >= 60)
    strcpy(remark, "Good work! You can do even better.");
   else
    strcpy(remark, "Fair. Focus more on studies.");
} else {
   strcpy(status, "Fail");
   strcpy(remark, "Needs Improvement. Don’t give up!");
}

//Ganerate the REPORT CARD
fprintf(file,"----- Report Card -----\n");
fprintf(file,"Name         : %s\n", Name);
fprintf(file,"Roll No      : %d\n\n", RollNo);

fprintf(file,"Subjects and Marks:\n");
fprintf(file,"Maths        : %u\n", marks1);
fprintf(file,"Physics      : %u\n", marks2);
fprintf(file,"Chemistry    : %u\n", marks3);
fprintf(file,"English      : %u\n", marks4);
fprintf(file,"Computer     : %u\n", marks5);

fprintf(file,"\nTotal Marks  : %.2f / 500\n", total);
fprintf(file,"Percentage   : %.0f%%\n", percentage);
fprintf(file,"Grade        : %s\n", grade);
fprintf(file,"Result       : %s\n", status);
fprintf(file,"Remark       : %s\n", remark);
fclose(file);  // Close the file

//Mirror the output to console 
printf("----- Report Card -----\n");
printf("Name         : %s\n", Name);
printf("Roll No      : %d\n\n", RollNo);

printf("Subjects and Marks:\n");
printf("Maths        : %u\n", marks1);
printf("Physics      : %u\n", marks2);
printf("Chemistry    : %u\n", marks3);
printf("English      : %u\n", marks4);
printf("Computer     : %u\n", marks5);

printf("\nTotal Marks  : %.2f / 500\n", total);
printf("Percentage   : %.0f%%\n", percentage);
printf("Grade        : %s\n", grade);
printf("Result       : %s\n", status);
printf("Remark       : %s\n", remark);
 
    return 0;
}