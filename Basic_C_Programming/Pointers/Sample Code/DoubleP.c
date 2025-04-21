// 🧪 Code: Using Double Pointer to Handle Multiple Strings

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

    int num_studentes;
    printf("Enter the number of students: ");
    scanf("%d", &num_studentes);
    getchar();  // <--- This line clears the leftover newline from the buffer


    char **students = (char **)malloc(num_studentes * sizeof(char *));  //
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    //Alocate memory for each name and store
    for (int i = 0; i<num_studentes; i++){

        char temp[100];  //temporary buffer to read input
        printf("Enter the name of student %d: \n", i+1);
        fgets(temp, sizeof(temp), stdin);

        // ✅ Remove newline character if present
        temp[strcspn(temp, "\n")] = 0;

        // Allocate memory for each string and copy from temp
        students[i] = (char *)malloc(strlen(temp) + 1);
        strcpy(students[i], temp);
    }
    
      // Print all names
      printf("\nStudent List:\n");
      for (int i = 0; i < num_studentes; i++) {
          printf("%s\n", students[i]);
      }
  
      // Free memory
      for (int i = 0; i < num_studentes; i++) {
          free(students[i]);
      }
      free(students);
  
      return 0;

 }
