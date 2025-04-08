/*
Write a C program to manage electricity bill calculation for multiple customers.

The program should:

    Ask the number of customers.

    For each customer, accept: Customer ID, Name, Units consumed.

    Calculate bill amount as per this slab:

        First 100 units: ₹1.5 per unit, 101–300 units: ₹2.5 per unit, Above 300 units: ₹4.0 per unit
        Add a surcharge of 10% if bill exceeds ₹1000

    Display customer details and final bill amount (with surcharge if applicable)

Bonus: Add type casting to format bill values to float. */

#include <stdio.h>
#define Max_name_Length 100    // macro of char array of size 100

int i, n;  // Tokens: int, =, ; | Identifiers: i, n

int main(){

    unsigned int Unit_Consumed, Customer_ID;
    char name[Max_name_Length];
    float bill, surcharge=0.0, total;

    printf("Enter the number of the custoners: ");
    scanf("%d", &n);   

    for (i = 0; i <n ; i++){               //loop to handle details for multiple customers
        printf("\n Enter details for the customer %d\n", i+1);

        printf("Customer ID:");
        scanf("%u", Customer_ID);   

        printf("Name:");
        scanf("%s", &name);        //To read the string with spaces

        printf("Unit Consumed: ");
        scanf("%u", &Unit_Consumed);

    
    //Bill calculation based on slab
    if (Unit_Consumed <=100)                        //First 100 units: ₹1.5 per unit
       bill == Unit_Consumed*1.5;                   
    else if (Unit_Consumed <=300)                   //101–300 units: ₹2.5 per unit
       bill = (100 *1.5)+ ((Unit_Consumed - 100)*2.5);
    else 
       bill = (100*1.5) + (200 * 2.5) + ((Unit_Consumed - 300) * 4.0);         // Above 300 units: ₹4.0 per unit       
    
    // Apply surcharge if bill > 1000
     
    if (bill > 1000) {
        surcharge = bill * 0.10;  // 10% surcharge
    }

    total = (float)(bill + surcharge);                   //surcharge of 10% if bill exceeds ₹1000

    printf("\n--- Customer Bill ---\n");
    printf("Customer ID   : %u\n", Customer_ID);
    printf("Name          : %s\n", name);
    printf("Units Consumed: %u\n", Unit_Consumed);
    printf("Bill Amount   : ₹%.2f\n", bill);
    printf("Surcharge     : ₹%.2f\n", surcharge);
    printf("Total Bill    : ₹%.2f\n", total);
   }
    return 0;
}