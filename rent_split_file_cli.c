#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_CODE_INVALID_NUMBER_OF_COMMAND_LINE_ARGUMENTS 101
#define ERROR_CODE_FILE_PATH_EXCEEDS_MAX_LENGTH 201
#define ERROR_CODE_FILE_PATH_HAS_NO_PERIOD 202
#define ERROR_CODE_FILE_PATH_HAS_MULTIPLE_PERIODS 203
#define ERROR_CODE_INVALID_FILE_EXTENSION 204
#define ERROR_CODE_OUTPUT_FILE_FAILED_TO_OPEN 301
#define ERROR_CODE_OUTPUT_FILE_PATH_STRING_MEMORY_ALLOCATION_FAIL 401
#define ERROR_CODE_TOTAL_RENT_INPUT_STRING_EXCEEDS_MAX_LENGTH 501
#define ERROR_CODE_TOTAL_RENT_INPUT_STRING_MEMORY_ALLOCATION_FAIL 601
#define ERROR_CODE_TOTAL_RENT_EXCEEDS_MAX_VALUE 701

#define MAX_LENGTH_TOTAL_RENT_INPUT_STRING 11
#define MAX_TOTAL_RENT 20000000
#define MAX_ALLOWED_PATH_LENGTH 260

/* 
NOTE TO SELF: Build a function for printing errors and returning error codes because this has gotten ridiculous 
Search for locations where to put that function by searching for all return statements or all uses of the word "error"
*/

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("ERROR\n");
        printf("\tInvalid number of command-line arguments\n");
        printf("\tUsage: %s <total_rent> <name_of_txt_file>\n", argv[0]);
        printf("\tError Code: %d\n", ERROR_CODE_INVALID_NUMBER_OF_COMMAND_LINE_ARGUMENTS);

        return ERROR_CODE_INVALID_NUMBER_OF_COMMAND_LINE_ARGUMENTS;
    }

    /* 
    Check that argv[2] is a valid name for a txt file.
    Maybe also check that the user isn't overwriting anything important, though I'm not sure how to do that.
    */

    /* 
    ##################################

    DEALING WITH argv[2] BELOW

    ##################################
    */
    int length_of_given_output_file = strlen(argv[2]);
    if (length_of_given_output_file >= MAX_ALLOWED_PATH_LENGTH) {
        printf("ERROR\n");
        printf("\tLength of path for output txt file exceeds the maximum allowed value of %d characters\n", MAX_ALLOWED_PATH_LENGTH - 1);
        printf("\tError Code: %d\n", ERROR_CODE_FILE_PATH_EXCEEDS_MAX_LENGTH);
        return ERROR_CODE_FILE_PATH_EXCEEDS_MAX_LENGTH;
    }

    char *output_file = (char *) malloc((length_of_given_output_file + 1) * sizeof(char));
    if (!output_file) {
        printf("ERROR\n");
        printf("\tError Code: %d\n", ERROR_CODE_OUTPUT_FILE_PATH_STRING_MEMORY_ALLOCATION_FAIL);
        return ERROR_CODE_OUTPUT_FILE_PATH_STRING_MEMORY_ALLOCATION_FAIL;
    }

    strcpy(output_file, argv[2]);

    char *ptr_to_period_in_output_file_path = strchr(output_file, '.');
    if (!ptr_to_period_in_output_file_path) {
        printf("ERROR\n");
        printf("\tFile paths need to have a period somewhere but this one doesn't\n");
        printf("\tError Code: %d\n", ERROR_CODE_FILE_PATH_HAS_NO_PERIOD);
        return ERROR_CODE_FILE_PATH_HAS_NO_PERIOD;
    }

    char *ptr_to_second_period_in_output_file_path = strchr(ptr_to_period_in_output_file_path + 1, '.');
    if (ptr_to_second_period_in_output_file_path) {
        printf("ERROR\n");
        printf("\tFile paths cannot have more than one period but this one does\n");
        printf("\tError Code: %d\n", ERROR_CODE_FILE_PATH_HAS_MULTIPLE_PERIODS);
        return ERROR_CODE_FILE_PATH_HAS_MULTIPLE_PERIODS;
    }

    if (strcmp(ptr_to_period_in_output_file_path, ".txt")) {
        printf("ERROR\n");
        printf("\tOutput file given must be a txt file, and so the second argument requires the \".txt\" file extension\n");
        printf("\tError Code: %d\n", ERROR_CODE_INVALID_FILE_EXTENSION);
        return ERROR_CODE_INVALID_FILE_EXTENSION;
    }

    FILE *file_ptr_rent_split_txt = fopen(output_file, "w");
    if (!file_ptr_rent_split_txt) {
        printf("ERROR\n");
        printf("\tError Code: %d\n", ERROR_CODE_OUTPUT_FILE_FAILED_TO_OPEN);
        return ERROR_CODE_OUTPUT_FILE_FAILED_TO_OPEN;
    }

    free(output_file);
    
    
    /* 
    Check that argv[1] is a string containing only numbers and at most one decimal point.
    If there are more than 2 digits after the decimal point but everything else is okay, abort program and yell at user.
    */

    /* 
    ##################################

    DEALING WITH argv[1] BELOW

    ##################################
    */
    int length_total_rent_input_string = strlen(argv[1]);
    if (length_total_rent_input_string > MAX_LENGTH_TOTAL_RENT_INPUT_STRING) {
        printf("ERROR\n");
        printf("\tError Code: %d\n", ERROR_CODE_TOTAL_RENT_INPUT_STRING_EXCEEDS_MAX_LENGTH);
        return ERROR_CODE_TOTAL_RENT_INPUT_STRING_EXCEEDS_MAX_LENGTH;
    }

    char *total_rent_input_string = (char *) malloc((length_total_rent_input_string + 1) * sizeof(char));
    if (!total_rent_input_string) {
        printf("ERROR\n");
        printf("\tMemory allocation failed for total_rent_input_string\n");
        printf("\tError Code: %d\n", ERROR_CODE_TOTAL_RENT_INPUT_STRING_MEMORY_ALLOCATION_FAIL);
        return ERROR_CODE_TOTAL_RENT_INPUT_STRING_MEMORY_ALLOCATION_FAIL;
    }
    strcpy(total_rent_input_string, argv[1]);

    int total_rent = 0;

    /* own version of function that converts from string to num_pennies */
    for (int i = 0, num_periods = 0, current_digit; i < length_total_rent_input_string; i++) {
        current_digit = total_rent_input_string[i];
        if (current_digit == '.') {
            if (num_periods > 0) {
                printf("ERROR\n");
                return -1;
            }
            num_periods++;
        } else {
            if (current_digit < '0' || current_digit > '9') {
                printf("ERROR\n");
                return -1;
            } else {
                total_rent *= 10;
                total_rent += current_digit - '0';
            }
        }
    }

    free(total_rent_input_string);

    if (total_rent % 2 != 0) {
        printf("ERROR\n");
        printf("\tMy bad, the program can only deal with rents that end with even numbers right now. Will be fixed later.\n");
        return -1;
    }

    int even_split = total_rent / 2;

    int take_out;
    
    int lower_rent, lower_rent_dollar, lower_rent_cent;
    
    int higher_rent, higher_rent_dollar, higher_rent_cent;

    int cost_above_even_split, cost_above_even_split_dollar, cost_above_even_split_cent;


    /* 
    Definitely way too much arithmetic happening in this for-loop.
    Basically all thats happening is numbers are going up and down by 1. 
    When those numbers hit 0 or 99 they circle back around, incredibly straightforward.
    */
    for (int difference = 0, difference_dollar, difference_cent; difference <= total_rent; difference += 2) {
        take_out = total_rent - difference;
        lower_rent = take_out / 2;
        higher_rent = (take_out / 2) + difference;

        lower_rent_dollar = lower_rent / 100;
        lower_rent_cent = lower_rent % 100;

        higher_rent_dollar = higher_rent / 100;
        higher_rent_cent = higher_rent % 100;

        difference_dollar = difference / 100;
        difference_cent = difference % 100;

        cost_above_even_split = higher_rent - even_split;
        cost_above_even_split_dollar = cost_above_even_split / 100;
        cost_above_even_split_cent = cost_above_even_split % 100;

        fprintf(file_ptr_rent_split_txt, "lower rent:%6d.%.2d\t\t", lower_rent_dollar, lower_rent_cent);
        fprintf(file_ptr_rent_split_txt, "higher rent:%6d.%.2d\t\t", higher_rent_dollar, higher_rent_cent);
        fprintf(file_ptr_rent_split_txt, "difference:%6d.%.2d\t\t", difference_dollar, difference_cent);
        fprintf(file_ptr_rent_split_txt, "cost above 50%% split:%6d.%.2d\n\n", cost_above_even_split_dollar, cost_above_even_split_cent);
    }

    /* Printing extra new lines at the end. Small problem but should be fixed. */

    fclose(file_ptr_rent_split_txt);

    return 0;
}