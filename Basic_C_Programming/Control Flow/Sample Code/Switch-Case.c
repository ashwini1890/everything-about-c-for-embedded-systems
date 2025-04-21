/* 
Switch-Case — Menu-Driven Temperature Converter

Problem Statement:
Convert temperature from Celsius to Fahrenheit or vice versa using a menu.

The formula for converting Celsius (°C) to Fahrenheit (°F) is:  
°F = (°C × 9/5) + 32 

The formula to convert Fahrenheit to Celsius is:
°C = (°F - 32) × 5/9.
You can also write it as
°C = (°F - 32) / 1.8
*/

#include <stdio.h>

int main (){
    int choice;
    float celsius, fahrenheit;

    printf("=====Temperature Converter=======");
    printf("1.  Convert Fahrenteit to Celsius\n");
    printf("2.  Convert Celsius to Fahrenteit\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
        printf("Enter Temperatire in Celsius: ");
        scanf("%f",celsius);
        fahrenheit= (celsius * 9 / 5) + 32;
        printf("Temperature in Fahrenheit: %.2f F",fahrenheit);
        break;

        case 2:
        printf("Enter Temperatire in Fahrenheit: ");
        scanf("%f",fahrenheit);
        celsius  = (fahrenheit - 32) / 1.8;
        printf("Temperature in celsius t: %.2f F",celsius);
        break;

        default:
            printf("Invalid choice! Please enter 1 or 2.\n");
            break;
    }
   
}
