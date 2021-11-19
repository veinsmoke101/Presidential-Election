#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int pres_id = 0;
int voters_number = 0;

typedef struct president{
    int votes;
    int id;
    char * name;
    struct president * next;
}president;


president * createPresident(char * );
void addPresident(president ** , char * );
void deletePresident(president** , president *);
void printPresident(president* );
int vote(president** ,int );
int premierTour(president ** );
void resetVotes(president **);
int deuxiemeTour(president ** );
int dernierTour(president ** );






int main()
{

    president * head = NULL; // initialize empty president list
    char ** voters = (char**)malloc(sizeof(char*)); // initialize empty voters list
    char *data = NULL;
    unsigned int len = 0;
    int i,vote_data,tour_result;

    // Read Candidate Presidents
    printf("Enter Candidate Presidents :\n");
    do{
    data = NULL;
    getline(&data,&len,stdin);
    if(!strcmp(data,"0\n")){
        if(pres_id < 5){
            printf("Not Enough presidents !!\n");
            continue;
        }
        break;
    }

    addPresident(&head,(char *)data);

    }while(1);
    //system("cls");

    // Read voters
    printf("Enter CIN of Voters :\n");

    do{
    data = NULL;
    getline(&data,&len,stdin);
    if(!strcmp(data,"0\n")){
        if(voters_number < 10){
            printf("Not Enough candidates !!\n");
            continue;
        }
        break;
    }
    voters_number++;
    voters = (char**)realloc(voters,sizeof(char*)*voters_number);
    voters[voters_number - 1] = (char *)malloc(sizeof(char)*strlen(data));
    voters[voters_number - 1] = data;
    }while(1);
    system("clear");
//    for(i = 0;i<voters_number;i++)
//        printf("%s\n",voters[i]);
    printPresident(head);
    printf("Presidents number = %d\nVoters number = %d",pres_id,voters_number);

    i = 0;


    while(1){
        i = 0;
        printf("\n -----------------Premier tour----------------- \n");
        resetVotes(&head);
        do{
            do{
                printf("\nVoter of CIN : %sPlease vote now : ",voters[i]);
                scanf("%d",&vote_data);
                if(vote(&head,vote_data) == 1){
                    printf("Thank You\n");
                    break;
                }else{
                    printf(" .. Try again plz\n");
                }
            }while(1);

            i++;
        }while(i < voters_number);

        tour_result = premierTour(&head);
        if(tour_result == 1)
            break;

    }
    system("cls");
    printPresident(head);

        while(1){
        i = 0;
        printf("\n -----------------Deuxieme tour----------------- \n");
        resetVotes(&head);
        do{
            do{
                printf("\nVoter of CIN : %sPlease vote now : ",voters[i]);
                scanf("%d",&vote_data);
                if(vote(&head,vote_data) == 1){
                    printf("Thank You\n");
                    break;
                }else{
                    printf(" .. Try again plz\n");
                }
            }while(1);

            i++;
        }while(i < voters_number);

        tour_result = deuxiemeTour(&head);
        printf("%d",tour_result);
        if(tour_result == 1)
            break;

    }
    system("cls");
    printPresident(head);


    while(1){
        i = 0;
        printf("\n -----------------Dernier tour----------------- \n");
        resetVotes(&head);
        do{
            do{
                printf("\nVoter of CIN : %sPlease vote now : ",voters[i]);
                scanf("%d",&vote_data);
                if(vote(&head,vote_data) == 1){
                    printf("Thank You\n");
                    break;
                }else{
                    printf(" .. Try again plz\n");
                }
            }while(1);

            i++;
        }while(i < voters_number);

        tour_result = dernierTour(&head);
        if(tour_result == 1)
            break;

    }

    return 0;
}



president * createPresident(char * name){

    president * pres = (president *)malloc(sizeof(president));
    if(pres == NULL){
        printf("Allocation Error");
        exit(0);
    }
    pres_id++;
    pres->id = pres_id;
    pres->name = name;
    pres->votes = 0;
    pres->next = NULL;


    return pres;
}

void addPresident(president** head, char * name){

    president * newP = createPresident(name);
    if(*head == NULL){
        *head = newP;
    }
    else{
        president * temp = *head;
        newP->next = temp;
        *head = newP;

        //this will add to end of list
        /* while(temp->next != NULL)
        temp = temp->next;
        temp->next = newP;*/
    }
}

void deletePresident(president** head, president *pres){
    if(*head == NULL){
        printf("Can't perform deletion from empty list ");
    }else{
        president *temp = *head, *prev;

        if (temp != NULL && temp->id == pres->id) {
        *head = temp->next;
        free(temp);
        return;
        }


        while (temp != NULL && temp->id != pres->id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;


        prev->next = temp->next;

        free(temp);
    }
}



void printPresident(president * head){
    if(head == NULL)
        printf("Empty list\n");
    else{
        president * temp = head;
        printf("The list of Candidate Presidents :\n");
        while(temp != NULL){
            printf("Vote id = %d, name = %s\n",temp->id,temp->name);
            temp = temp->next;
        }
    }
}

int vote(president** head,int id){
    president *temp = *head;
    while(temp != NULL && temp->id != id){
        temp = temp->next;
    }
    if(temp==NULL){
        printf("President not found");
        return 0;
    }
    temp->votes++;
    return 1;
}

void resetVotes(president** head){
    president *temp = *head;
    while(temp != NULL ){
        temp->votes = 0;
        temp = temp->next;
    }
}


int premierTour(president ** head){
    president * temp = *head, *deleted = NULL;
    float result, count =0;
    while(temp != NULL && temp->next != NULL){
        if(temp->votes != temp->next->votes){
            count++;
            break;
        }
        temp=temp->next;
    }
    if(count == 0)
        return 0;

    temp = *head;
    while(temp != NULL){
        result = (temp->votes*100)/voters_number;
        if(result < 15){
            deleted = temp;
            printf("Eliminated president : %s",deleted->name);
            deletePresident(head,deleted);
        }
        temp = temp->next;
    }
    return 1;
}



int deuxiemeTour(president ** head){
    president * temp = *head, *deleted = NULL;
    float count =0;
    int min;
    while(temp != NULL && temp->next != NULL){
        if(temp->votes != temp->next->votes){
            count++;
            break;
        }
        temp=temp->next;
    }
    if(count == 0)
        return 0;

    temp = *head;
    deleted = temp;
    min = temp->votes;
    while(temp != NULL && temp->next != NULL){
        if(temp->next->votes < min)
            min = temp->next->votes;
        temp = temp->next;
    }
    temp = *head;
    while(temp != NULL ){
    if(temp->votes == min){
        printf("%d , ",temp->votes);
        deleted = temp;
        deletePresident(head,deleted);
    }
    temp = temp->next;
    }
    return 1;
}


int dernierTour(president ** head){
    president * temp = *head;
    int  max;

    max = temp->votes;

    while(temp != NULL && temp->next != NULL){
        if(temp->next->votes > max){
            max = temp->next->votes;
        }
        temp = temp->next;
    }

    temp = *head;
    while(temp != NULL && temp->next != NULL){
        if(temp->next->votes == temp->votes && temp->votes == max){
            return 0;
        }
        temp = temp->next;
    }

    temp = *head;
    while(temp != NULL ){
        if(temp->votes == max){
            system("cls");
            printf("\nLadies and Gentlemans .. Our Beloved President is :\n%s",temp->name);
            return 1;
        }
        temp = temp->next;
    }
    return 1;
}
