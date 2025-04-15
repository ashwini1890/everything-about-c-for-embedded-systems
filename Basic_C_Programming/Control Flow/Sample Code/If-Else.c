/*
Create a program that asks the user for a student's percentage.
It should classify the grade:

    ≥90: A

    80–89: B

    70–79: C

    60–69: D

    <60: F
    Also check if the input is between 0 and 100. If not, show an error.
*/

#include <stdio.h>

float percentage;

int main(){
// Greading System

    printf("Enter the Student's Percentage: ");
    scanf("%f",&percentage);
    
    if(percentage < 0 || percentage > 100)
    printf(" ERROR: Invalid data. \nData should be between 0-100 \n");
    else if(percentage >= 90)
    printf("Grade: A\n");
    else if(percentage >= 80)
    printf("Grade: B\n"); 
    else if(percentage >= 70)
    printf("Grade: C\n");
    else if(percentage >= 60)
    printf("Grade: D\n");
    else if(percentage < 60)
    printf("Grade: F\n");   

    return 0;

}