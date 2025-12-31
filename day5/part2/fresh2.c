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

int range_cmp (const void  *range1, const void  *range2);

int main (int argc, char *argv[]){
    Range *ranges; /* array of ranges */
    FILE *input;
    char read_buf[READ_SIZE];
    int range_count = 0;
    int capacity = 0; /* used for only resizing when needed */
    int base = 10;
    unsigned long total_fresh = 0;
    Range current;
    int i;


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

    /* once we have ranges we sort the ranges and then try to simplify the ranges and combine them */
    qsort(ranges, range_count, sizeof(Range), range_cmp); /* sorting ranges by starting value */
    current = ranges[0]; /* pointer to start of range array */
    
    /* 
        this is going to work by checking the current range with the next one, if it overlaps it will extend the current 
        range and then 
    */
    for (i = 1; i < range_count; i++) {
        if (ranges[i].start <= current.end + 1) { /* this prevents us from recounting ranges that overlap and means we have to merge ranges */
            if (ranges[i].end > current.end) /* we'll merge this range and update the current ending if we need to */
                current.end = ranges[i].end;
        } else { /* otherwise because this doesn't overlap with anything we can just add the range */
            total_fresh += current.end - current.start + 1;
            current = ranges[i];
        }
    }
    total_fresh += current.end - current.start + 1;


    printf("Total Fresh Ingredients %lu \n", total_fresh);
    return 0; /* exiting main successfully */

    cleanup:
        free(ranges);
}

int range_cmp (const void *range1, const void *range2){
    const Range *ra = range1;
    const Range *rb = range2;
    return (ra->start > rb->start) - (ra->start < rb->start); /* sorting like this to avoid large negative and positive numbers */
    /* this returns -1 to 1 inclusive */
}

