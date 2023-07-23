/*
a. Read a sequence of natural numbers (sequence ended by 0) and
 determine the number of 0 digits of the product of the read numbers.
b. Given a vector of numbers, find the longest contiguous subsequence
 such that the sum of any two consecutive elements is a prime number.
 */
#include <stdio.h>

int determine0sOfProductOfElems(const int v[], int n) {
    int twos = 0, fives = 0;
    for (int i = 0, x; i < n; ++i) {
        x = v[i];
        while (x % 2 == 0)
            twos++, x /= 2;
        while (x % 5 == 0)
            fives++, x /= 5;
    }
    return twos < fives ? twos : fives;
}

#define MILLION 1000000
short int notPrimes[MILLION]; // 1 if is prime and 0 if not prime

void eratosteneSieve() {
    notPrimes[0] = notPrimes[1] = 1;
    for (int i = 2; i * i < MILLION; ++i) {
        for (int j = 2; i * j < MILLION; ++j) {
            notPrimes[i * j] = 1;
        }

    }
}

void longestContiguousSubsequenceSumOfTwoConsecutiveElementsPrime(const int v[], int n, int *start, int *end) {
    int currentLength = 1, maxLength = 1;
    for (int i = 1; i < n; ++i) {
        if (notPrimes[v[i] + v[i - 1]] == 0)
            currentLength++;
        else if (currentLength > maxLength) {
            *end = i - 1;
            *start = i - currentLength;
            maxLength = currentLength;
            currentLength = 1;
        }
        else
            currentLength = 1;
    }
    if (currentLength > maxLength) {
        *end = n - 1;
        *start = n - currentLength;
        maxLength = currentLength;
        currentLength = 1;
    }
}

void printSequenceVector(int v[], int start, int end){
    for (int i = start; i <= end; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void printMenu(){
    printf("r - Read a sequence of natural numbers (sequence ended by 0) \n"
           "a - determine the number of 0 digits of the product of the read numbers.\n"
           "b - Given a vector of numbers, find the longest contiguous subsequence\n"
           "such that the sum of any two consecutive elements is a prime number.\n"
           "x - to exit\n");
}

void getOption(char* option){
    printf("option:");
    if(*option != 'x')
        getchar();
    scanf_s("%c", option);
}

int readVector(int v[]){
    int n = 0;
    printf("Enter the numbers:");
    scanf_s("%d", (v + n));
    n++;
    while (v[n - 1] != 0)
        scanf_s("%d", (v + n)), n++;
    return (n - 1);
}

int main() {
    char option = 'x';
    printMenu();
    getOption(&option);
    int v[100] = {0}, n = 0;
    eratosteneSieve();
    while (option != 'x') {
        if (option == 'r')
            n = readVector(v);
        else if (option == 'a') {
            printf("The number of digits of the read number is: %d\n", determine0sOfProductOfElems(v, n));
        } else if (option == 'b') {
            int start = -1, end = -1;
            longestContiguousSubsequenceSumOfTwoConsecutiveElementsPrime(v, n, &start, &end);
            printSequenceVector(v, start, end);
        } else {
            printf("Invalid command");
        }
        getOption(&option);
    }
    return 0;
}