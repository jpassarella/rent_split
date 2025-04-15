#include <stdio.h>
#include <stdlib.h>

#define ERROR_CODE_WRITE_FILE_FAILED_TO_OPEN 201

int main(int argc, char **argv) {
    FILE *file_ptr_rent_split_txt = fopen("rent_split.txt", "w");
    if (!file_ptr_rent_split_txt) {
        exit(ERROR_CODE_WRITE_FILE_FAILED_TO_OPEN);
    }
    
    int total_rent = 267670;

    int even_split = total_rent / 2;

    int take_out;
    
    int lower_rent, lower_rent_dollar, lower_rent_cent;
    
    int higher_rent, higher_rent_dollar, higher_rent_cent;

    int cost_above_even_split, cost_above_even_split_dollar, cost_above_even_split_cent;


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

    fclose(file_ptr_rent_split_txt);

    return 0;
}