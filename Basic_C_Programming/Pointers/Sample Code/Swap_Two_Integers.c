/*
Write a function swap(int *a, int *b) that swaps two integers in-place using pointers. 
In main, read two integers, print their addresses and values before and after calling swap.
Show how dereferencing (*) accesses/changes the value at an address.
*/

#include<stdio.h>


//call by referance argumment to manipulate the original value of the variable
void swap(int *a , int *b){
    if(!a || !b)return;
    int temp = *a;
    *a=*b;
    *b= temp;

}

int main(){
    int x=50, y=100;
    
    printf("Before: x=%d (addr=%p), y=%d (addr=%p)\n", x, (void*)&x, y, (void*)&y);
    swap(&x, &y); // pass addresses
    printf("After : x=%d (addr=%p), y=%d (addr=%p)\n", x, (void*)&x, y, (void*)&y);

    return 0;
}
