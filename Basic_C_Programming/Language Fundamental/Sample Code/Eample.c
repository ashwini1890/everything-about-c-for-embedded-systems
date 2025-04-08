/*Create a C program that calculates the Body Mass Index (BMI) of a person.
The user should enter their weight (in kg) and height (in cm).
The program should:

    Calculate BMI using the formula:
    BMI=weight in kg(height in meters)2
    BMI=(height in meters)2weight in kg​

    Classify the BMI into:

        Underweight: BMI < 18.5

        Normal: 18.5 ≤ BMI < 24.9

        Overweight: 25 ≤ BMI < 29.9

        Obese: BMI ≥ 30 */

#include <stdio.h>



//Keywords utilised: int, float, return, if, else
//Identifiers utilised: bmi, weight, height_cm, height_m
// Token Utilised:  =, +, /, *, (), {}

float weight, hight_m, bmi;
unsigned int height_cm;      //only positive values

int main(){

    printf("Enter the weight in Kg: ");   //weight
    scanf("%f", &weight);

    printf("Enter the hight in cm: ");   //Hight in c
    scanf("%u",&height_cm);

    hight_m = (float)height_cm/100;    //type casting

    printf("Hight in m: %.2f\n", hight_m);   //Hight in m

    bmi = weight/(hight_m*hight_m);       //BMI Calculation
    printf("BMI of the person is: %.2f\n", bmi);

    if(bmi< 18.5)
    printf("Category: Underweight\n");
    else if (bmi >= 18.5 && bmi < 24.9)
        printf("Category: Normal\n");
    else if (bmi >= 25 && bmi < 29.9)
        printf("Category: Overweight\n");
    else
        printf("Category: Obese\n");
    return 0;  // return: keyword, returns control to OS

}