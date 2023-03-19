#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
    char vtype[6];
    char vnumber[11];
    char entry[4];
    struct node* prev;
    struct node* next;
};

struct node* createNode(char type[], char number[], char en_try[]) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->vtype, type);
    strcpy(newNode->vnumber, number);
    strcpy(newNode->entry, en_try);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertFront(struct node** head_ref, char type[], char number[], char en_try[]) {
    struct node* newNode = createNode(type, number, en_try);
    if (*head_ref == NULL) {
        *head_ref = newNode;
    } else {
        newNode->next = *head_ref;
        (*head_ref)->prev = newNode;
        *head_ref = newNode;
    }
}

void deleteRear(struct node** head_ref) {
    if (*head_ref == NULL) {
        printf("There are no vehicles.\n");
    } else {
        struct node* temp = *head_ref;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        if (temp->prev == NULL) {
            *head_ref = NULL;
        } else {
            temp->prev->next = NULL;
        }
        free(temp);
    }
}

int fee(struct node** head_ref, char exxit[]){
	struct node* temp = *head_ref;
	if (*head_ref == NULL) {
        printf("There are no vehicles.\n");
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
}
	int a = abs(strcmp(exxit, temp->entry));
	int fee = a*10;
	return fee;
}

int main() {
	printf("\t\t\t\t\tNICE ROAD TOLL FEE COLLECTION SYSTEM\n");
    struct node* head = NULL;
    int choice;
    char type[6], number[11], en_try[4], exxit[4];
    FILE *file;
    file = fopen("contents.txt", "w");
    int vv = 1;
    while (1) {
        printf("1. Vehicle enter\n");
        printf("2. Vehicle exit\n");
        printf("3. Exit program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter vehicle type, entry direction and vehicle number: ");
                scanf("%s", type);
		    fprintf(file, "%d\tVehicle type: %s\t\n", vv, type);
		    int valid1 = 1;
                if (strlen(type) > 4) {
                valid1 = 0;
                }
                for (int i = 0; i < strlen(type); i++) {
                if (!isalpha(type[i])) {
                    valid1 = 0;
                    break;
                }
                }
                if (!valid1) {
                printf("Invalid type of vehicle\n");
                break;
                }	
		    scanf("%s", en_try);
		    fprintf(file, "%d\tEntry point: %s\t\n", vv, en_try);
		    int valid2 = 1;
                if (strlen(en_try) > 4) {
                valid2 = 0;
                }
                for (int i = 0; i < strlen(en_try); i++) {
                if (!isalpha(en_try[i])) {
                    valid2 = 0;
                    break;
                }
                }
                if (!valid2) {
                printf("Invalid Entry point. Please enter only among BNR, ELC, KPR, MYS, TMR.\n");
                break;
                }		
		    scanf("%s", number);
		    fprintf(file, "%d\tVehicle number: %s\t\n", vv, number);
                int valid = 1;
                if (strlen(number) > 10) {
                valid = 0;
                }
                for (int i = 0; i < strlen(number); i++) {
                if (!isalnum(number[i])) {
                    valid = 0;
                    break;
                }
                }
                if (!valid) {
                printf("Invalid number\n");
                break;
                }
                insertFront(&head, type, number, en_try);
                break;
            case 2:
		    printf("\nEnter the exit point\n");
		    scanf("%s", exxit);
		    int valid3 = 1;
                if (strlen(exxit) > 4) {
                valid3 = 0;
                }
                for (int i = 0; i < strlen(exxit); i++) {
                if (!isalpha(exxit[i])) {
                    valid3 = 0;
                    break;
                }
                }
                if (!valid3) {
                printf("Invalid Exit point. Please exit only among BNR, ELC, KPR, MYS, TMR. Make sure to input an exit point that is different than your 			    entry point\n");
                break;
                }		
		    printf("\nThe fee is: %d\n", fee(&head, exxit));
		    fprintf(file, "%d\tExit point: %s\t\n", vv, exxit);
                deleteRear(&head);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    vv++;
	}
   fclose(file);
   return 0;
}
