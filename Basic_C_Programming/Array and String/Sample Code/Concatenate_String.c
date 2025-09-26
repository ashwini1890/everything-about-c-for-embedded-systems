/*Write a C program to manually implement string copy and string concatenation 
operations (without using built-in library functions like strcpy or strcat).*/

#include<stdio.h>

char str1[100],str2[100], copy[100];

void copy_string(char temp[], char src[]){
    int i = 0;
    while( src[i]!='\0'){
        temp[i] = src[i];
        i++;
    }
    temp[i]='\0';
}

void str_concat(char temp[], char src[]){

    int i=0,j=0;
    while (temp[i]!='\0')i++;
       
    temp[i]=' ';
    i++;
    
    while (src[j]!='\0') {
         temp[i] = src[j];
        i++; j++;
    }
    
    temp[i] = '\0';
    
}

int main(){
    printf("Enter 1st string: ");
    scanf("%s",str1);
    printf("Enter 2nd string: ");
    scanf("%s", str2);

    copy_string(copy,str1);
    printf("The coped string temp from String 1 is: %s\n", copy );
    str_concat(str1,str2);
    printf("The resultent string after concatination of both the strings is: %s\n", str1 );

    return 0;
}