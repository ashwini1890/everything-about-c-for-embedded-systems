/*Write a C program that takes a sentence as input and counts the following in the string:

Vowels → Characters a, e, i, o, u (case-insensitive).

Consonants → All alphabets except vowels.

Digits → Numeric characters 0-9.

Spaces → Space characters ' '.

Finally, display the total number of vowels, consonants, digits, and spaces separately.*/ 

#include<stdio.h>
#include<ctype.h>

int vowels, Consonants, Digits, Spaces;

int main(){

    char str[1000];
    printf("Enter a string: ");
    scanf("%[^\n]",str);

    //to transverse each character in the alphabet
    for(int i = 0; str[i]!='\0';i++){
        char ch = tolower(str[i]);

        if(ch >='a' && ch <='z'){
            if(ch=='a'|| ch=='e'|| ch=='i' || ch=='o' || ch=='u')
                vowels++;
            else Consonants++;
        }
        else if(ch >='0' && ch<='9'){
            Digits++;
        }
        else if (ch == ' ') Spaces++;
    }

    printf("Vowels: %d\nConsonants: %d\nDigits: %d\nSpaces: %d\n", vowels, Consonants,Digits, Spaces);
    return 0;
}