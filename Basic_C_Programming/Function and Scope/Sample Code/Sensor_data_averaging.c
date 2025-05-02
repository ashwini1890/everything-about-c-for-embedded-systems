/*
📝 Problem Statement:

Simulate reading sensor data multiple times and calculate the average value. Use functions to separate the concerns of reading data
and computing the average.
💡 Learning Objectives:

    Practice passing arrays to functions.

    Understand local vs. global variable scope.
*/
#include <stdio.h>
void readSensorData(int* data, int size);
float averageValue(int* data, int size);


// Function to simulate reading sensor data
void readSensorData(int *data, int size) {
    for (int i = 0; i < size; i++) {
        // Simulate sensor data reading
        // Replace with actual sensor reading logic
        data[i] = i * 10; 
    }
}

// Function to calculate average of sensor data
float averageValue(int *data, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return (float)sum / size;
}

int main(){
    int sensorData[5];

    // Read sensor data
    readSensorData(sensorData, 5);

     // Calculate average
     float average =averageValue(sensorData, 5);

     // Display average
     printf("Average Sensor Value: %.2f\n", average);
 
     return 0;
 
}