//Write a program to check whether a given number is even or odd. 

#include <stdio.h>
int a;
int main(){

    printf("Enter an integer: ");
    scanf("%d", &a);

    if (a %2 ==0){
        printf("The given number is even");
    }
    else{
        printf("The given number is odd");
    }
}