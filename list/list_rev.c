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
    list *sub_list=head->next;
    head->next=NULL;
    while(sub_list!=NULL)
    {
        list *sub_next=sub_list->next;
        list *head_next=head->next;
        head->next=sub_list;
        sub_list->next=head_next;
        sub_list=sub_next;
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
