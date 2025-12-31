#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_SIZE 1024

void parse_input(char ***matrix, int *row_len, int *col_len);

int main (int argc, char *argv[]){
    int row_len = 0;
    int col_len = 0;
    char **matrix = NULL;
    int i,j;
    int accessible = 0;


    parse_input(&matrix, &row_len, &col_len);


    /* loop over each item and then check bounds to see what we can check with */
    for (i = 0; i < row_len; i++) {
        for (j = 0; j < col_len; j++) {
            int count = 0; /* see how many @'s there are in the adjacent squares*/

            /* first check if we are at a paper roll */
            if ('@' != matrix[i][j]){
                /* if we're not at a paper roll we print out the character and skip the rest of the loop */
                printf("%c", matrix[i][j]); 
                continue;
            }
            
            /* checking adjacent squares logic */

            /*
                NOTE: you'll see I check for both a paper roll and an x
                that's because already visited paper rolls will be changed to an 
                x not an @ but they still need to be counted */

            /* checking if a row above exists */
            if (i > 0){

                /* directly above square check */
                if ('@' == matrix[i-1][j] || 'x' == matrix[i-1][j]){
                    count += 1;
                }

                /* top left square check */
                if (j > 0 && ('@' == matrix[i-1][j-1] || 'x' == matrix[i-1][j-1])){ /* short circuiting will keep this line safe */
                    count += 1;
                }

                /* top right square check */
                if (j < (col_len - 1) && ('@' == matrix[i-1][j+1] || 'x' == matrix[i-1][j+1])){ /* short circuiting will keep this line safe */
                    count += 1;
                }
            }


            /* checking if a row below exists */
            if (i < (row_len - 1)){

                /* directly below square check */
                if (('@' == matrix[i+1][j] || 'x' == matrix[i+1][j])){
                    count += 1;
                }

                /* bottom left square check */
                if (j > 0 && ('@' == matrix[i+1][j-1] || 'x' == matrix[i+1][j-1])){ /* short circuiting will keep this line safe */
                    count += 1;
                }

                /* bottom right square check */
                if (j < (col_len - 1) && ('@' == matrix[i+1][j+1] || 'x' == matrix[i+1][j+1])){ /* short circuiting will keep this line safe */
                    count += 1;
                }
            }

            /* checking left square */
            if (j > 0 && ('@' == matrix[i][j-1] || 'x' == matrix[i][j-1])){
                count += 1;
            }

            /* checking right square */
            if (j < (col_len - 1) && ('@' == matrix[i][j+1] || 'x' == matrix[i][j+1])){
                count += 1;
            }

            /* if we are below the count the paper can be accessed */
            if (count < 4){
                matrix[i][j] = 'x';
                accessible += 1;
            }

            /* now print out the character (after you've either left it alone or changed it!)*/
            printf("%c", matrix[i][j]);
            
        }
        printf("\n");
    }
    printf("Total Rolls Accessible %d \n", accessible);
}


void parse_input(char ***matrix, int *row_len, int *col_len){
    char read_buf[READ_SIZE];
    FILE *input;
    int row = 0;
    int length;
    int cleanup_idx;
    char **tmp;

   

    input = fopen("input.in", "r");
    if (NULL == input){
        printf("Error trying to open input file \n");
        exit(1);
    }

    

    /* 
        running fgets once to determine the length of the rows in the matrix 
        to ensure future rows are also the same length
        this is done just to check potential bad inputs
    */

    
    

    if (NULL != fgets(read_buf, READ_SIZE, input)){
        /* allocating one row */
        *matrix = malloc(sizeof(char *));
        if (!*matrix) {
            printf("Error trying to malloc \n");
            exit(1);
        }
        
        read_buf[strcspn(read_buf, "\n")] = '\0'; /* trimming new lines from end of input to ensure standardized size */
        length = strlen(read_buf);
        (*matrix)[row] = malloc(length); /* allocate space on the matrix for the new row */
        if (NULL == (*matrix)[row]){
            printf("Error with trying to allocate space for current row \n");
            goto cleanup;
        }
        strncpy((*matrix)[row], read_buf, length);
        row++; /* if all is successful we update our row index */

        tmp = realloc(*matrix, (row+1) * sizeof(char *));
        if (!tmp) {
            printf("Error trying to allocate space for a new row in matrix \n");
            goto cleanup;
        }
        *matrix = tmp;
    }


    while(NULL != fgets(read_buf, READ_SIZE, input)){
        read_buf[strcspn(read_buf, "\n")] = '\0'; /* trimming new lines from end of input to ensure standardized size */
        if (length != strlen(read_buf)){
            printf("Error, inputs not the same length, matrix not possible \n");
            goto cleanup;
        }
        (*matrix)[row] = malloc(length); /* allocate space on the matrix for the new row */

        if (NULL == (*matrix)[row]){
            printf("Error with trying to allocate space for current row \n");
            goto cleanup;
        }

        strncpy((*matrix)[row], read_buf, length);
        row++; /* if all is successful we update our row index */

        /* adding more space */
        tmp = realloc(*matrix, (row+1) * sizeof(char *));
        if (!tmp) {
            printf("Error trying to allocate space for a new row in matrix \n");
            goto cleanup;
        }
        *matrix = tmp;
    }

    *row_len = row;
    *col_len = length;

    if (-1 == fclose(input)){
        printf("Failed to close file \n");
        goto cleanup;
    }

    return;


    cleanup:
        printf("CLEANING UP");
        for (cleanup_idx = 0; cleanup_idx < row; cleanup_idx++){
            free((*matrix)[row]); /* free the row's contents */
        }
        free(*matrix); /* free on NULL guaranteed to be safe */
        exit(1);        
}
