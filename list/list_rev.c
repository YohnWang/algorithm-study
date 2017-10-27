#include<stdio.h>
#include<stdlib.h>

struct list
{
    int data;
    struct list *next;
};
typedef struct list list;

void list_rev(list *head)
{
    list *first=head->next;
    list *sub_list;
    if(first==NULL)
        return ;  //list is empty
    sub_list=first->next;
    first->next=NULL; //first node turn to end

    list *tmp=sub_list;
    list *next,*insert=first;
    while(tmp!=NULL)
    {
        next=tmp->next;
        tmp->next=insert;
        insert=tmp;
        head->next=tmp;
        tmp=next;
    }
}


void print_list(list *head)
{
    list *p=head->next;
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}

int main(int argc,char *argv[])
{
    list *head,*tmp;
    head=malloc(sizeof(*head));
    tmp=head;

    for(int i=0;i<10;i++)
    {
        list *p=malloc(sizeof(*p));
        p->data=i;
        tmp->next=p;
        tmp=p;
    }
    tmp->next=NULL;
    print_list(head);
    printf("\n");
    list_rev(head);
    print_list(head);

}
