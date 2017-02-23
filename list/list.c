#include<stdio.h>
#include<stdlib.h>
typedef struct list list;
struct list
{
    list *prev;
    list *next;
};

void list_init(list *p)
{
    p->prev=p;
    p->next=p;
}

void list_insert(list *p,list *new)
{
    list *p_next;
    p_next=p->next;
    p->next=new;
    p_next->prev=new;
    new->next=p_next;
    new->prev=p;
}

void list_del(list *entry)
{
    list *prev,*next;
    prev=entry->prev;
    next=entry->next;
    prev->next=next;
    next->prev=prev;
}

void list_for_each(list *p,void (*handler)(list *p,void *args),void *args)
{
    list *head=p;
    do
    {
        handler(p,args);
        p=p->next;
    }while(p!=head);
}

struct fox
{
    list list;
    int weight;
};
typedef struct fox fox;

void print_weight(list *p,void *args)
{
    printf("%d ",((fox*)p)->weight);
}

int main(int argc,char *argv[])
{
    fox *f;
    f=malloc(sizeof(fox));
    f->weight=100;
    list_init(&f->list);
    fox *x;
    x=malloc(sizeof(fox));
    x->weight=200;
    list_insert(&f->list,&x->list);
    x=malloc(sizeof(fox));
    x->weight=300;
    list_insert(&f->list,&x->list);
    x=malloc(sizeof(fox));
    x->weight=400;
    list_insert(&f->list,&x->list);
    list_for_each(&f->list,print_weight,NULL);
    printf("\n");
    list_del(&x->list);
    list_for_each(&f->list,print_weight,NULL);
}
