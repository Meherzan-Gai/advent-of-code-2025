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
    for (i = start; i <= end; i++){
        snprintf(val_buf, sizeof(val_buf), "%lu", i);
        length = strlen(val_buf);
        
        if (length % 2 == 0){
            if (strncmp(val_buf, val_buf + length/2, length/2) == 0){
                total += i;
            }
        }
    }
    return total;
}
