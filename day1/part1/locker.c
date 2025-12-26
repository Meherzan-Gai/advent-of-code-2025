#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#define READ_SIZE 15
#define LETTER_SPACE 1 

int main (int argc, char *argv[]){
    FILE *input;
    char read_buff[READ_SIZE];
    long amount;
    int rotate_val;

    char *endptr;

    int count = 0;
    int base = 10;
    int curr = 50; /* we start at 50 on the locker */
    int modval = 100;

    input = fopen("input.in", "r");

    if (NULL == input){
        printf("Error trying to open input file \n");
        exit(1);
    }

    while (NULL != fgets(read_buff, READ_SIZE, input)){
        errno = 0;
        amount = strtol(read_buff+LETTER_SPACE, &endptr, base);

        if (read_buff+LETTER_SPACE == endptr){
            printf("No digits were found \n");
            exit(1);
        }

        if ((errno == ERANGE) || (amount > INT_MAX) || (amount < INT_MIN)){
            printf("Number out of range \n");
            exit(1);
        }

        rotate_val = (int)amount; /* safe conversion now that checks are done */

        if ('L' == read_buff[0]){
            curr -= rotate_val;
        } else if ('R' == read_buff[0]){
            curr += rotate_val;
        } else {
            printf("Issue with parsing direction \n");
            exit(1);
        }

        curr = ((curr % modval) + modval) % modval; /* mod can return negatives so this ensures a positive value */

        if (0 == curr){
            count += 1;
        }
    }

    printf("Total count: %d \n", count);
}
