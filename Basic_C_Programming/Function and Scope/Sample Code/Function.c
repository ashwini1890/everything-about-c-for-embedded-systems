/*
Problem Statement:

Write a C program to perform basic arithmetic operations (addition, subtraction, multiplication, and division) 
using different types of functions:

    Function with no return type and no arguments

    Function with return type but no arguments

    Function with arguments but no return type

    Function with return type and arguments
*/

#include <stdio.h>

//initialise the function
void greeting();
int getchoice();
float operate(int, float, float);
void printResult(float);



int main (){

    float num1, num2, result;

    int choice;
    greeting();                              //function with no argument no return;
    
    printf("Enter two Numbers: ");
    scanf("%f %f", &num1, &num2);

    choice = getchoice();                     //No argument, with return

    result = operate(choice, num1, num2);    // Return, with args 
    printResult(result);                     // No return, with argument

    return 0;
}

//function with no argument no return
void greeting(){
    printf("====== Welcome to the Calculator ======\n");
}

//function with no argument, with return
int getchoice(){
    int A;    //variable Scope type - local
    printf("Choose operation:\n1.Add\n2.Subtract\n3.Multiply\n4.Divide\nEnter choice: ");
    scanf("%d",&A);
    return A;
}

//function with Return, with args 
float operate(int x, float a, float b){
    switch(x){
        case 1: return a + b;
        case 2: return a - b;
        case 3: return a * b;
        case 4: return b != 0 ? a / b : 0;    //a one-liner alternative to a simple if-else 
        default:
        printf("Invalid operation choice!\n");
        return 0;
    }
}

// Funtion with no return type, With arguments
void printResult(float result) {
    printf("Result: %.2f\n", result);
}