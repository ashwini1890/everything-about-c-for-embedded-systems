/*Given an integer array, compute the sum by walking the array with a pointer (not indexing).
Print the effect of p+1 (how it advances by sizeof(int) bytes).*/

#include<stdio.h>

int main(){
    int array[]={25,24,10,60,20,13};
    int n = (int)(sizeof array/sizeof array[0]);
    
    int *p = array;
    long long int sum = 0;
    
    printf("the value of element in array is: %d\n", n);

    for( int i=0; i<n; i++){
        sum += *p;
        p = p+1;
     }

    printf("The sum of the array is: %lld\n", sum);
    
    // Demonstrate addresses & arithmetic
    int *p0 = &array[0];
    int *p1 = p0 + 1;
    printf("Address array[0]=%p, array[1]=%p, byte differance ~ %td\n",(void*)p0, (void*)p1, (char*)p1 - (char*)p0);


    return 0;
}
