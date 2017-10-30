#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define List_Length (50)
#define Number_Max (20)

//it must be compiled whit the c99 supported compiler

typedef struct list list;
struct list
{
    int data;
    list *next;
};


void list_remove(list *head)
{
    int table[Number_Max]={0};
    list *ptr=head->next;
    list *prv=head;
    while(ptr!=NULL)
    {
        int value=abs(ptr->data);
        if(table[value]==0)
        {
            table[value]=1;
            prv=ptr;
            ptr=ptr->next;
        }
        else
        {
            list *del=ptr;
            ptr=ptr->next;
            free(del);
            prv->next=ptr;
        }
    }
}


void list_print(list *head)
{
    list *ptr=head->next;
    while(ptr!=NULL)
    {
        printf("%d ",ptr->data);
        ptr=ptr->next;
    }
    printf("\n");
}

int main(int argc,char *argv[])
{

    //construct list
    list *head=malloc(sizeof(*head));
    list *ptr=head;
    for(int i=0;i<List_Length;i++)
    {
        int v=(int)(rand()%(Number_Max*2))-Number_Max;
        list *l=malloc(sizeof(*l));
        l->data=v;
        ptr->next=l;
        ptr=l;
    }
    ptr->next=NULL;

    list_print(head);

    list_remove(head);
    list_print(head);
}
