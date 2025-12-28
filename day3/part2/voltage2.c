/* 
Thinking about how I can edit this code to work for 12 digit voltages instead
I realize that I can create a for loop that loops through digits 1 to 12.
I can then calculate the max length to loop through so that a 12 digit number can still be made
I will also add the values as I go instead of storing them in variables to add at the end
(Because it doesn't matter what other digits I find once I find the first max digit, so I might as well add it right away)

I will also convert the integer to a long

*/

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
    unsigned long total_voltage = 0;

    input = fopen("input.in", "r");

    if (NULL == input){
        printf("Error trying to open input file \n");
        exit(1);
    }

    while (fgets(read_buf, READ_SIZE, input) != NULL){
        unsigned int i;
        unsigned int max_idx;
        char cur_char;
        unsigned int cur_digit;
        unsigned int prev_max_idx;
        unsigned long adjusted_val;
        int exponent;
        long power;
        int power_idx;

        read_buf[strcspn(read_buf, "\n")] = '\0'; /* trimming new lines from input to ensure standardized size */


        
        /* going to loop through each character in the line and convert it to an int */

        /* find the index of the largest number (excluding the last number)
            we want to find the earliest occurence of the largest number hence we'll ensure that in our checks
            (this gives us more opportunity to find a larger 2nd digit)
        */
        length = strlen(read_buf);

        if (-1 == length){
            printf("Error trying to get length of input line \n");
            exit(1);
        } else if (11 >= length){
            printf("Error line not long enough (need at least 12 digits) \n");
            exit(1);
        }

        /* first ensuring all lines have a null terminator right after it */

        /* printf("LENGTH OF STRING %d \n", length); */

        max_idx = 0;
        prev_max_idx = -1;


        for (cur_digit=0; cur_digit < 12; cur_digit++){ /* looping through each digit in the 12 digit value */
            max_idx = prev_max_idx + 1;

            /* DEBUGGING 
            printf("CUR DIGIT %d \n", cur_digit);
            printf("STARTING INDEX %d \n", prev_max_idx+1);
            printf("LENGTH BOUND %d \n", length - (11-cur_digit));
            printf("MAX INDEX %c \n", read_buf[max_idx]);
            */

            for (i = prev_max_idx + 1; i < length-(11-cur_digit); i++){ /* length  - (11-cur_digit) to avoid the last 11-cur_digit values in the line */
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
                prev_max_idx = max_idx; /* set the previous max index to start from to the max index */
            }
            
            /* adding max value to total */

            /* computing exponent manually to be safe */
            power = 1;
            exponent = 11 - cur_digit;
            for (power_idx = 0; power_idx < exponent; power_idx++) {
                if (power > LONG_MAX / 10) {
                    exit(1);
                }
                power *= 10;
            }

            adjusted_val = (read_buf[max_idx] - '0') * power;
            if (adjusted_val == LONG_MAX){
                printf("Long int overflow error found, exiting \n");
                exit(1);
            }
            
            /* printf("ADJUSTED VAL %lu \n" , adjusted_val); */

            total_voltage += adjusted_val;
            if (total_voltage == LONG_MAX){
                printf("Long int overflow error found, exiting \n");
                exit(1);
            }
            

            /* printf("MAX INDEX FOUND FOR THAT DIGIT %d \n", max_idx); */
        }
        /* printf("CURR TOTAL %lu \n", total_voltage); */
        
    }

    printf("TOTAL VOLTAGE %lu \n", total_voltage);
}
