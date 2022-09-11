#include <stdio.h>
#include <stdlib.h>

int recursion(int x){
    if(x==0){
        return 2;
    }
    else{
        return 3 * (x-1) + recursion(x-1) + 1;
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Syntax Error: Arglen must be %d  \n", 2);
        return EXIT_SUCCESS;
    }

    int num;
    int str_check = sscanf(argv[1], "%d", &num);

    if(str_check == 0){
        printf("Please input a non-negative integer\n");
        return EXIT_SUCCESS;
    }
    else{
        printf("%d\n", recursion(num));
        return EXIT_SUCCESS;
    }
}