//Creating a 2D Dynamic Array to Store Sensor Data (e.g., temperature values)

#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3;    // Number of sensors
    int cols = 4;    // Number of time readings per sensor

    // Step 1: Allocate memory for 'rows' number of int pointers (each will point to an int array)
    int **sensor_data = (int **)malloc(rows * sizeof(int *));
    if (sensor_data == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    // Step 2: For each row, allocate memory for 'cols' integers
    for (int i = 0; i < rows; i++) {
        sensor_data[i] = (int *)malloc(cols * sizeof(int));
        if (sensor_data[i] == NULL) {
            printf("Memory allocation failed at row %d!\n", i);
            return -1;
        }
    }

    // Step 3: Assign sample temperature values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sensor_data[i][j] = (i + 1) * 10 + j;  // Just dummy data
        }
    }

    // Step 4: Print the 2D array (sensor readings)
    printf("Sensor Data:\n");
    for (int i = 0; i < rows; i++) {
        printf("Sensor %d: ", i + 1);
        for (int j = 0; j < cols; j++) {
            printf("%d ", sensor_data[i][j]);
        }
        printf("\n");
    }

    // Step 5: Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(sensor_data[i]);  // Free each row
    }
    free(sensor_data);         // Free the array of pointers

    return 0;
}
