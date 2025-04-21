/*
Nested If — ATM PIN Verification with Balance Check

Problem Statement:
Ask the user for a PIN. If correct, allow withdrawal.
 If the amount is higher than the balance, deny it.
*/

#include <stdio.h>
int pin, ATM_PIN, Amount;
float balance; 

int main(){
    
    pin = 1890;
    balance = 50000;

    printf("Enter the Pin: ");
    scanf("%d", &ATM_PIN);

    if (ATM_PIN == pin){
        printf("Withdrawal Amount: ");
        scanf("%d", &Amount);
        
        if(Amount <= balance){
            printf("Collect your Cash from window on the RIGHT\n");

            balance -= Amount;       //Updated Balance
            printf("Your Current Balance is: %.2f",balance);
        }else{
            printf("Insufficient balance\n"); 
        }
    
    }else
    printf("Incorrect PIN \nPlease Try again\n");

    return 0;
}
