// In do-while statement the code is executed once before checking the conditions

/*
📘 Problem Statement: Number Guessing Game with Replay Option

Create a number guessing game in C where:

    The program randomly generates a number between 1 and 100.

    The user has to guess the number.

    After each guess, the program tells the user if their guess is too high, too low, or correct.

    The user keeps guessing until the correct number is guessed — use a while loop for this.

    After the game ends, the user is asked if they want to play again — use a do-while loop to allow replaying the game.
*/



#include <stdio.h>
#include <stdlib.h> //for rand() and srand()
#include <time.h>   // For time()

int num, randum, attemptCount;
char playAgain;

int main(){

    // Seed the random number generator with current time
   
    srand(time(NULL));
     /*time(NULL)This value changes every second, so it gives a different seed every time you run the program.
        As a result, rand() gives you different random numbers each run.*/

    printf("===== Welcome to the Number Gyessing Game! ========\n\n");    
    // Outer loop: Do-While for replaying the game
    do {
        // Generate a random number between 1 and 100
        randum = (rand() % 100) + 1;
        attemptCount = 0;  // Reset number of guesses for each game

        printf("\nI have picked a number between 1 and 100.\n");
        printf("Try to guess it!\n");

        // Inner loop: While loop for guessing until the correct number is found
        while (1){

            printf("Guess the num: ");
            scanf("%d", &num);
            attemptCount++;  //chech the number of attempts 

            if (num < randum) {
                printf("Too low! Try again.\n");
            } else if (num > randum) {
                printf("Too high! Try again.\n");
            } else {
                printf("Correct! You guessed it in %d attempts.\n", attemptCount);
                break;  // Exit the guessing loop
            }
        }
        
        // Ask if the user wants to play again
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain); // Note the space before %c to consume newline

    }
    
    while (playAgain == 'y' || playAgain == 'Y');

    printf("Thanks for playing! Goodbye.\n");

    return 0;
}