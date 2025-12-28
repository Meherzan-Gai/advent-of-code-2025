#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define READ_SIZE 256

unsigned long find_invalid_total(unsigned long start, unsigned long end);



int main (int argc, char *argv[]){
    FILE *input;
    char read_buff[READ_SIZE];
    unsigned long total = 0;
    int base = 10;


    input = fopen("input.in", "r");

    if (NULL == input){
        printf("Error trying to open input file \n");
        exit(1);
    }

    while (NULL != fgets(read_buff, READ_SIZE, input)){
        char *range_saveptr;
        char *ranges = strtok_r(read_buff, ",", &range_saveptr);
        while (ranges != NULL) {
            char *limit_saveptr;
            char *start = strtok_r(ranges, "-", &limit_saveptr);
            char *end   = strtok_r(NULL, "-", &limit_saveptr);

            if (NULL != start && NULL != end) {
                unsigned long start_val = strtoul(start, NULL, base);
                unsigned long end_val = strtoul(end, NULL, base);

                total += find_invalid_total(start_val, end_val);
            }
            ranges = strtok_r(NULL, ",", &range_saveptr);
        }
    }

    printf("Total: %lu \n", total);
}

unsigned long find_invalid_total(unsigned long start, unsigned long end){
    unsigned long total = 0;
    char val_buf[30];
    int length = 0;
    unsigned long i;
    

    /* adjust to find pattern through all */
    for (i = start; i <= end; i++){
        unsigned int pattern_length;
        unsigned int invalid_bool;
        snprintf(val_buf, sizeof(val_buf), "%lu", i);
        length = strlen(val_buf);

        pattern_length = 1;
        invalid_bool = 0;
        for (pattern_length=1; pattern_length < (length/2) + 1; pattern_length++){
            if (0 == length % pattern_length){ /* if the pattern length divides the number's length we check it*/
                unsigned int num_pattern = length/pattern_length; /* finds how many of the pattern will occur */
                /* so if the pattern length we are checking for is 2 and the string length is 10, we will repeat the pattern 5 times */
                unsigned int count = 0;
                unsigned int pattern_found = 1;
                while (count < num_pattern && 1 == pattern_found){
                    if (strncmp(val_buf, val_buf + (pattern_length * count), pattern_length) != 0){
                        pattern_found = 0; /* the pattern is no longer valid, exit */
                    }
                    count += 1;
                }
                if (1 == pattern_found){
                    invalid_bool = 1; /* we found an invalid number*/
                    /* printf("INVALID NUMBER FOUND %lu \n", i); */
                    /* printf("INVALID PATTERN %d \n", pattern_length); */
                }
            }
        }
        if (1 == invalid_bool){
            total += i; /* add the number if it was found invalid by some pattern*/
            /* printf("INVALID NUMBER FOUND %lu \n", i); */
        }
    }
    return total;
}
