#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Get hash function and hash all values in the ranges, then go through the list of ingredients, hash, and see if it 
exists in the hash table (1 at a time?) */


#define READ_SIZE 256
/* a struct to store the starts and ends of ranges found */
typedef struct {
    unsigned long start;
    unsigned long end;
} Range;


int main (int argc, char *argv[]){
    Range *ranges; /* array of ranges */
    FILE *input;
    char read_buf[READ_SIZE];
    int range_count = 0;
    int capacity = 0; /* used for only resizing when needed */
    int base = 10;
    unsigned long total_fresh = 0;


    input = fopen("input.in", "r");

    if (NULL == input){
        printf("Error trying to open input file \n");
        exit(1);
    }

    /* getting ranges */
    while (NULL != fgets(read_buf, READ_SIZE, input)){
        char *start = NULL;
        char *end = NULL;

        /* ranges are done once we see the newline */
        if (0 == strncmp(read_buf, "\n", 1)){
            break; 
        }
        start = strtok(read_buf, "-");
        end = strtok(NULL, "-");

        if (NULL != start && NULL != end) {
            unsigned long start_val = strtoul(start, NULL, base);
            unsigned long end_val = strtoul(end, NULL, base);

            /* adding to ranges list */
            if (range_count == capacity) {
                if (capacity == 0){
                    capacity = 8;
                } else{
                    capacity *= 2;
                }
                ranges = realloc(ranges, capacity * sizeof(Range));
                if (ranges == NULL) {
                    printf("Reallocation for ranges failed \n");
                    goto cleanup;
                }
            }
            ranges[range_count].start = start_val;
            ranges[range_count].end = end_val;
            range_count += 1;
        }
    }

    while (NULL != fgets(read_buf, READ_SIZE, input)){
        /* idea here is to loop through each range and see if the integer falls in between any of them */
        int idx = 0;
        unsigned long val;

        val = strtoul(read_buf, NULL, base);

        for (idx = 0; idx < range_count; idx++){
            if (ranges[idx].start <= val && val <= ranges[idx].end){
                total_fresh += 1;
                if (total_fresh == __LONG_MAX__){
                    printf("Error long overflow detected \n");
                    goto cleanup;
                }
                break; /* we can break out of looking for whether this number fits in any ranges once we find one */
            }
        }
    }

    printf("Total Fresh Ingredients %lu \n", total_fresh);
    return 0; /* exiting main successfully */

    cleanup:
        free(ranges);
}
