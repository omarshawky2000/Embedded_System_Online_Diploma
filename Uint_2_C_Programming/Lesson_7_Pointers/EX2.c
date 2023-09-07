#include <stdio.h>
#define ALPHABET_SIZE 26

int main() {
    char capitalAlphabets[ALPHABET_SIZE];

    char *ptr = capitalAlphabets;
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        *ptr = ch;
        ptr++;
    }
    ptr = capitalAlphabets; 
    printf("Capital Alphabets: ");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", *ptr);
        ptr++; 
    }
    printf("\n");

    return 0;
}
