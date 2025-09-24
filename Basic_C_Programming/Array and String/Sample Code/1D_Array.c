// Find the Largest Element in a 1D Array

#include<stdio.h>

int main(){
    int array[] = {10,20,80,60,30};
    int max = array[0];
   

    for (int i = 1; i < 5; i++){
        if(array[i] > max){
            max = array[i];
        }

    }
     printf("Largest element = %d\n", max);
    return 0;
}