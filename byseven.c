#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Syntax Error: Arglen must be %d \n", 2);
        return EXIT_SUCCESS;
    }

    int number_of_times = atoi(argv[1]);

    if(number_of_times <= 0){
        printf("Error: Must be a number larger than 0 \n");
        return EXIT_SUCCESS;
    }

    int i;
    for(i = 1; i<= number_of_times; i++){
        int to_print = 7*i;
        printf("%d \n", to_print);
    }
    
    return EXIT_SUCCESS;
}