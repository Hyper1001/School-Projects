/*
George Vo
1001360024
Coding Assignment 1
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
typedef struct node
{
    int number;
    struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    struct node* temp = *LinkedListHead;
    newNode->number=Number;
    if(*LinkedListHead==NULL)
    {
        *LinkedListHead=newNode;

    }
    else
    {
        while(temp->next_ptr!=NULL)
        {
            temp = temp->next_ptr;
        }
        temp->next_ptr = newNode;
    }
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{

    FILE *fp;
    fp=fopen(argv[1],"r");
    int place;
    int count=0;
    int sum=0;
    while(!feof(fp))
    {
        fscanf(fp,"%d",&place);
        if(!feof(fp))
        {
            AddNodeToLL(place, LLH);
            sum+=place;
            count++;
        }
    }
    printf("\n%d records were read for a total sum of %d.\n",count,sum);
    fclose(fp);
}

void PrintLL(NODE *LLH)
{
    struct node* temp = LLH;
    while(temp!=NULL)
    {
        printf("\n%p %d %p\n",temp,temp->number,temp->next_ptr);
        temp = temp->next_ptr;
    }
}

void FreeLL(NODE **LLH)
{
    struct node* temp = *LLH;
    struct node* next;
    int sum=0;
    int count=0;
    while(temp!=NULL)
    {
        #ifdef PRINT
            printf("\nFreeing %p %d %p\n",temp,temp->number,temp->next_ptr);
        #endif
        sum+=temp->number;
        next = temp->next_ptr;
        free(temp);
        temp = next;
        count++;
    }
    printf("\n%d records were deleted for a total sum of %d.\n",count,sum);
    *LLH = NULL;
}

int main(int argc, char *argv[])
{
    if(argc==1)
    {
        printf("File must be provided on command line...exiting\n");
    }
    else if(argc==2)
    {
        clock_t start;
        clock_t end;
        NODE *LLH = NULL;
        start = clock();
        ReadFileIntoLL(argc, argv, &LLH);
        end = clock();
        printf("\n%ld ticks to write the file into the linked list\n", end-start);

        #ifdef PRINT
            start = clock();
            PrintLL(LLH);
            end = clock();
            printf("\n%ld ticks to print the linked list\n", end-start);
        #endif

        start = clock();
        FreeLL(&LLH);
        end = clock();
        printf("\n%ld ticks to free the linked list\n", end-start);

        return 0;
    }
    else
    {
        printf("Too many arguments are provided...exiting\n");
    }
}
