#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define READ_SIZE 1024
#define BASE_10 10
int main (int argc, char *argv[]){
    FILE *input;
    char read_buf[READ_SIZE];
    int length;
    unsigned int total_voltage = 0;

    input = fopen("input.in", "r");

    if (NULL == input){
        printf("Error trying to open input file \n");
        exit(1);
    }

    while (fgets(read_buf, READ_SIZE, input) != NULL){
        unsigned int i;
        unsigned int max_idx;
        unsigned int second_max_idx;
        char cur_char;
        unsigned int first_digit;
        unsigned int second_digit;
        
        /* going to loop through each character in the line and convert it to an int */

        /* find the index of the largest number (excluding the last number)
            we want to find the earliest occurence of the largest number hence we'll ensure that in our checks
            (this gives us more opportunity to find a larger 2nd digit)
        */
        length = strlen(read_buf);

        if (-1 == length){
            printf("Error trying to get length of input line \n");
            exit(1);
        } else if (1 >= length){
            printf("Error line not long enough (need at least 2 digits) \n");
            exit(1);
        }

        max_idx = 0;


       
        for (i = 1; i < length-2; i++){ /* length - 2 to avoid the last value in the line (it can't be the first largest number)*/
            cur_char = read_buf[i];

            if ('\0' == cur_char){ /* safety check to stop the program if a null terminator is hit (shouldn't happen in theory) */
                printf("Null char found while parsing line \n");
                exit(1);
            } else if (0 == isdigit(cur_char)){
                printf("Non-digit value found while parsing line \n");
                exit(1);
            }

            if (cur_char > read_buf[max_idx]){ /* only greater than since we want to find the first occurence of the largest value */
                max_idx = i; /* set the new max digit index */
            }
        }


        second_max_idx = max_idx + 1; /* for now the digit right after max_idx is the largest second digit possible */
        for (i = max_idx + 2; i < length - 1; i++){ /* max_idx + 2 because max_idx + 1 is already set to the largest second digit*/
            cur_char = read_buf[i];

            if ('\0' == cur_char){ /* safety check to stop the program if a null terminator is hit (shouldn't happen in theory) */
                printf("Null char found while parsing line \n");
                exit(1);
            } else if (0 == isdigit(cur_char)){
                printf("Non-digit value found while parsing line \n");
                exit(1);
            }

            if (cur_char > read_buf[second_max_idx]){ /* only greater than since we want to find the first occurence of the second largest value */
                second_max_idx = i; /* set the new second largest digit index */
            }
        }

        /* DEBUGGING 
        printf("MAX IDX %d \n", max_idx);
        printf("SECOND DIGIT IDX %d \n", second_max_idx);
        */

        first_digit = (read_buf[max_idx] - '0') * 10; /* getting value from first digit */
        second_digit = read_buf[second_max_idx] - '0';
        total_voltage += (first_digit+second_digit); /* adding integer value to the total voltage */

        if ((total_voltage + (first_digit + second_digit)) >= INT_MAX){
            printf("Integer overflow error found, exiting \n");
            exit(1);
        }
    }

    printf("TOTAL VOLTAGE %d \n", total_voltage);
}
