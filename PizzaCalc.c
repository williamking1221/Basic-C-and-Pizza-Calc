#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14159265358979323846

struct Pizza{
    char name[64];
    float pizza_per_dollar;
    struct Pizza* next;
    struct Pizza* prior;
};

float calc_ppd(float d, float cost){
    if(d == 0 || cost == 0){
        return 0.000;
    }
    float area;
    area = d * d * PI / 4;
    return area / cost;
}

void swap(struct Pizza* p1, struct Pizza* p2){
    char temp[64];
    float temp_ppd;
    strcpy(temp, p1->name);
    temp_ppd = p1->pizza_per_dollar;
    strcpy(p1->name, p2->name);
    p1->pizza_per_dollar = p2->pizza_per_dollar;
    strcpy(p2->name, temp);
    p2->pizza_per_dollar = temp_ppd;
}

void bubble_sort(struct Pizza* head){
    struct Pizza* current = head;
    while(current->next != NULL){
        if(current->pizza_per_dollar < current->next->pizza_per_dollar){
            swap(current, current->next);
            //Continue comparing backwards to find the right spot for the node
            if(current->prior != NULL){
                current = current->prior;
            }
            else{
                current = current->next;
            }
        }
        else if (current->pizza_per_dollar == current->next->pizza_per_dollar){
            if(strcmp(current->name, current->next->name) > 0){
                swap(current, current->next);
                //Continue comparing backwards to find the right spot for the node
                if(current->prior != NULL){
                    current = current->prior;
                }
                else{
                    current = current->next;
                }
            }
            else{
                current = current->next;
            }
        }
        else if(current->pizza_per_dollar > current->next->pizza_per_dollar){
            current = current->next;
        }
    }
}

int main(int argc, char* argv[]){
    //Must have 2 args (Form: ./pizzacalc xxx.txt)
    if(argc != 2){
        printf("Syntax Error: Arglen must be %d\n", 2);
        return EXIT_SUCCESS;
    }

    //Open the file
    char* file_name = argv[1];
    FILE *f = fopen(file_name, "r");

    //Prepare variables and Create linked list
    char name_line[64];
    float diam;
    float price;
    float ppd;

    //Dealing with empty file
    if(f == NULL){
        printf("PIZZA FILE IS EMPTY\n");
        return EXIT_SUCCESS;
    }

    if(fscanf(f, "%s", name_line) == EOF){
        printf("PIZZA FILE IS EMPTY\n");
        return EXIT_SUCCESS;
    }

    if(strcmp(name_line, "DONE") == 0){
        printf("PIZZA FILE IS EMPTY\n");
        return EXIT_SUCCESS;
    }

    //Create linked list
    struct Pizza* head = (struct Pizza*) malloc(sizeof(struct Pizza));

    fscanf(f, "%f", &diam);
    fscanf(f, "%f", &price);
    ppd = calc_ppd(diam, price);

    strcpy(head->name, name_line);
    head->pizza_per_dollar = ppd;
    head->prior = NULL;
    head->next = NULL;

    struct Pizza* ptrfast = head;
    fscanf(f, "%s", name_line);
    while(strcmp(name_line, "DONE") != 0){
        fscanf(f, "%f", &diam);
        fscanf(f, "%f", &price);
        
        ppd = calc_ppd(diam, price);
        
        struct Pizza* temp = (struct Pizza*) malloc(sizeof(struct Pizza));
        ptrfast->next = temp;
        strcpy(temp->name, name_line);
        temp->pizza_per_dollar = ppd;
        temp->next = NULL;
        temp->prior = ptrfast;
        ptrfast = ptrfast->next;
        fscanf(f, "%s", name_line);
    }
    //Add sort function
    bubble_sort(head);

    fclose(f);
    while(head != NULL){
        printf("%s %f\n", head -> name, head -> pizza_per_dollar);
        ptrfast = head;
        head = head->next;
        free(ptrfast);
    }

    return EXIT_SUCCESS;
}