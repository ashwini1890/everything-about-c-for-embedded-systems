/*
🧩 Problem Statement

Design a Smart LED Controller system that simulates automatic LED control based on ambient light. The system should:

    Simulate reading light levels (e.g., using an LDR).

    Automatically turn ON the LED if the light level is below a threshold.

    Turn OFF the LED if light is above the threshold.

    Use functions to modularize:

        Sensor reading

        LED control

        Decision logic

    Practice global and local scopes effectively.

This is a simulation (i.e., without real hardware), but it mimics how embedded systems behave.
*/

#include <stdio.h>
#include <stdlib.h>  //standard library
#include <unistd.h>  //used in POSIX-compliant systems:  here for sleep
#include <time.h>   //Time Library


// ---------- Global Variables ----------
#define LIGHT_THRESHOLD 300  // Simulated threshold (0–1023 like ADC)
int ledState = 0;            // 0 = OFF, 1 = ON (global to simulate output pin)

// ---------- Function Declarations ----------
int readLightSensor();                 // Simulate reading light sensor
void controlLED(int lightLevel);       // Decide whether to turn ON/OFF LED
void turnOnLED();                      // Simulated LED ON
void turnOffLED();                     // Simulated LED OF

// ---------- Main Function ----------
int main() {
    srand(time(NULL));  // Seed for random sensor value simulation

    while (1) {
        int light = readLightSensor();  // Call to simulate ADC light input
        controlLED(light);              // Decide based on light level
        sleep(1);                       // Delay for 1 second
    }

    return 0;
}

// ---------- Function Definitions ----------

// Simulate light sensor reading (returns 0 to 1023 like ADC)
int readLightSensor() {
    int value = rand() % 1024;  // Simulate 10-bit ADC value
    printf("Ambient Light Level: %d\n", value);
    return value;
}

// Control logic: compare with threshold and update LED state
void controlLED(int lightLevel) {
    if (lightLevel < LIGHT_THRESHOLD) {
        if (ledState == 0) {
            turnOnLED();  // Only turn ON if currently OFF
        }
    } else {
        if (ledState == 1) {
            turnOffLED(); // Only turn OFF if currently ON
        }
    }
}

// Simulate turning ON LED
void turnOnLED() {
    ledState = 1;
    printf("LED TURNED ON (Low light detected)\n");
}

// Simulate turning OFF LED
void turnOffLED() {
    ledState = 0;
    printf("LED TURNED OFF (Sufficient light)\n");
}
