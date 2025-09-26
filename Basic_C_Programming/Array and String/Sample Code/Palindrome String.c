/* Palindrome String Check

📌 Practice: String manipulation with loops */

#include<stdio.h>
#include<string.h>

int main(){
    char string[100];
    printf("Enter a string: ");
    scanf(" %[^\n]", string);
    printf("%s\n", string);

    int len = strlen(string), flag =1;

    for(int i =0; i< len/2; i++){
        if(string[i] != string[len -i -1]){
            flag = 0;
            break;
        }
    }

    (flag) ?  printf("The string is a Palindrome") : printf("The string is NOT a Palindrome");

    return 0;
}