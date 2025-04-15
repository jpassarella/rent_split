#include <stdio.h>

int main(int argc, char **argv) {
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

        printf("lower rent:%6d.%.2d\t\t", lower_rent_dollar, lower_rent_cent);
        printf("higher rent:%6d.%.2d\t\t", higher_rent_dollar, higher_rent_cent);
        printf("difference:%6d.%.2d\t\t", difference_dollar, difference_cent);
        printf("cost above 50%% split:%6d.%.2d\n", cost_above_even_split_dollar, cost_above_even_split_cent);
    }

    return 0;
}