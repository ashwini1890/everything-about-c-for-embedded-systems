/*
 designing a temperature monitoring system for an industrial environment using a temperature sensor (e.g., LM35). The system should:

    Continuously monitor the temperature at regular intervals.

    Trigger an alert if the temperature exceeds a certain threshold (e.g., 50°C).

    Display the current temperature and the status of the system (whether the temperature is within the safe range or needs attention).
The system uses a microcontroller to read the analog value from the sensor, convert it to a digital value, and display it on a serial monitor.
The program must also provide feedback (alerts) when the temperature exceeds the threshold.
*/

#include <stdio.h>  //SStandard Input Output Header file: Provide functions for input and output operations.
#include<stdlib.h>  // Standard Library Header file:Provides functions for memory allocation, random number generation, process control, conversions, etc.
#include <unistd.h> // Provides access to the POSIX(Portable Operating System Interface.) operating system API. Used mainly on Linux/Unix systems.


// Function prototypes
void readTemperature(float* temp);              // Function to simulate reading the temperature (with arguments)
void checkTemperature(float temp);              // Function to check if temperature exceeds threshold (No return type, with argument)
void displayTemperature(float temp);            // Function to display temperature on the console (No return type, with argument)

// Temperature threshold
#define THRESHOLD 50.0

int main(){

    float currentTemperature;

    while(1) {
        // Simulate reading temperature from the sensor

        readTemperature(&currentTemperature);   //pass the address of currentTemperature using &currentTemperature

        // Display the current temperature
        
        displayTemperature(currentTemperature); // passing a copy of the value of currentTemperature

        // Check if temperature is within safe limits
        
        checkTemperature(currentTemperature);

        // Sleep for 1 second before reading again (simulating continuous monitoring)
        
        sleep(1); // This can be replaced with a timer interrupt in embedded systems
    }
    return 0;
}

/* Function to simulate reading the temperature from a sensor (with arguments)
 Simulating reading temperature for our use case  (in a real system, use ADC to read sensor data)*/

 void readTemperature(float* temp) {
    
    *temp = (rand() % 41) + 20; // Generates a random value between 20 and 60
    //*temp is assigned with the value of the variable pointed by temp and modifies the original value of currentTemperature
}


/*Function to display the current temperature (No return type, with arguments)
The function can read, print, manipulate value of currentTemperature locally — but it can't change the original.
*/ 

void displayTemperature(float temp) {
    printf("Current Temperature: %.2f°C\n", temp);
}

// Function to check if temperature exceeds the threshold (No return type, with arguments)
void checkTemperature(float temp) {
    srand(time(NULL)); // Seed random number generator
    if (temp >= THRESHOLD){
        printf("ALERT: Temperature %.2f°C exceeds threshold %.2f°C! Please check the system.\n, temp, THRESHOLD");
        printf("Turning on the Exhaust fan \n");

        sleep(3);

        printf("Turning OFF the Exhaust fan. Temperature is under control.\n");
        }
   else 
        printf("Temperature is within the safe range.\n");
 
}