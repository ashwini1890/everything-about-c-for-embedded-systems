/*
📘 Problem Statement: Prime Number Finder with Skips and Early Exit

Objective:
Write a C program that prints all prime numbers between 1 and 100, skipping multiples of 5,
and allowing the user to stop the program early if a specific number is reached (entered by user).
*/

#include <stdio.h>
int stopNumber;

int main(){
    printf("=================== Welcome to Prime Number Finder ===================\n\n");
    printf("Enter a number to stop at (if found as prime): ");
    scanf("%d", &stopNumber);

    printf("\nPrime Numbers from 1 to 100 (excluding multiples of 5):\n");

    
   // Loop through numbers from 2 to 100
   for (int i = 2; i <= 100; i++) {

    // Skip the number if it's a multiple of 5
    if (i % 5 == 0) {
        continue;  // go to the next iteration
    }

    // Check if i is a prime number
    int isPrime = 1; // assume prime
    for (int j = 2; j * j <= i; j++) {
        if (i % j == 0) {
            isPrime = 0; // not prime
            break;       // no need to check further
        }
    }

    // If it's prime, print it
    if (isPrime) {
        printf("%d\n", i);

        // If the prime number is equal to the user-defined stop number
        if (i == stopNumber) {
            printf("\nReached stop number %d. Exiting early.\n", stopNumber);
            break; // exit the main for loop
        }
    }
}

printf("\nProgram ended.\n");
return 0;
}