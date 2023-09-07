#include <stdio.h>
#include <stdlib.h>

int main() {
    int s;
    fflush(stdout);
    printf("Enter the size of the array: ");
    fflush(stdout);
    scanf("%d", &s);
    int* numbers = (int*)malloc(s * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed. Exiting the program.\n");
        return 1;}
    printf("Enter %d numbers:\n", s);
    fflush(stdout);
    for (int i = 0; i < s; i++) {
        scanf("%d", &numbers[i]); }
    printf("Numbers in reverse order: ");
    fflush(stdout);
    for (int i = s - 1; i >= 0; i--) {
        printf("%d ", *(numbers + i));}
    printf("\n");
    free(numbers);
    return 0;
}