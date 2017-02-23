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

inline list* list_next(list *p)
{
    return p->next;
}
inline list* list_prev(list *p)
{
    return p->prev;
}

struct polynomial
{
    list list;
    int factor;
    int power;
};
typedef struct polynomial polynomial;
void print_polynomial(int a[],int n)
{
    if(n<2)
        return ;
    int i=0;
    printf("%d",a[i]);
    printf("x^%d",a[i+1]);
    for(int i=2;i<n;i+=2)
    {
        printf("+%d",a[i]);
        printf("x^%d",a[i+1]);
    }
}

polynomial* create_polynomial(int a[],int n)
{
    if(n<2)
        return NULL;
    polynomial *p,*head;
    p=malloc(sizeof(*p));
    list_init(&p->list);
    p->factor=a[0];
    p->power=a[1];
    head=p;
    for(int i=2;i<n;i+=2)
    {
        polynomial *old=p;
        p=malloc(sizeof(*p));
        p->factor=a[i];
        p->power=a[i+1];
        list_insert(&old->list,&p->list);
    }
    return head;
}

void print_list(list *h,void *args)
{
    polynomial *p=(polynomial*)h,*head=args;
    if(p==head)
        printf("%dx^%d",p->factor,p->power);
    else
        printf("+%dx^%d",p->factor,p->power);
}


polynomial* add_polynomial(polynomial *a,polynomial *b)
{
    polynomial *sum,*sum_head,*a_head=a,*b_head=b;
    polynomial *end1=malloc(sizeof(*end1));
    list_insert(list_prev(&a->list),&end1->list);
    polynomial *end2=malloc(sizeof(*end2));
    list_insert(list_prev(&b->list),&end2->list);
    sum=malloc(sizeof(*sum));
    list_init(&sum->list);
    sum_head=sum;
    if(a->power==b->power)
    {
        sum->factor=a->factor+b->factor;
        sum->power=a->power;
        a=(polynomial*)list_next(&a->list);
        b=(polynomial*)list_next(&b->list);
    }
    else if(a->power<b->power)
    {
        sum->factor=a->factor;
        sum->power=a->power;
        a=(polynomial*)list_next(&a->list);
    }
    else
    {
        sum->factor=b->factor;
        sum->power=b->power;
        b=(polynomial*)list_next(&b->list);
    }
    while(a!=end1 && b!=end2)
    {
        polynomial *old=sum;
        sum=malloc(sizeof(*sum));
        if(a->power==b->power)
        {
            sum->factor=a->factor+b->factor;
            sum->power=a->power;
            a=(polynomial*)list_next(&a->list);
            b=(polynomial*)list_next(&b->list);
        }
        else if(a->power<b->power)
        {
            sum->factor=a->factor;
            sum->power=a->power;
            a=(polynomial*)list_next(&a->list);
        }
        else
        {
            sum->factor=b->factor;
            sum->power=b->power;
            b=(polynomial*)list_next(&b->list);
        }
        list_insert(&old->list,&sum->list);
    }
    while(a!=end1)
    {
        polynomial *old=sum;
        sum=malloc(sizeof(*sum));
        sum->factor=a->factor;
        sum->power=a->power;
        a=(polynomial*)list_next(&a->list);
        list_insert(&old->list,&sum->list);
    }
    while(b!=end2)
    {
        polynomial *old=sum;
        sum=malloc(sizeof(*sum));
        sum->factor=b->factor;
        sum->power=b->power;
        b=(polynomial*)list_next(&b->list);
        list_insert(&old->list,&sum->list);
    }
    list_del(&end1->list);
    list_del(&end2->list);
    return sum_head;
}

int main(int argc,char *argv[])
{
    int a[8]={1,0,10,2,5,7,1,10};
    int b[8]={1,1,10,2,1,7,3,11};
    print_polynomial(a,8);
    printf("\n");
    print_polynomial(b,8);
    printf("\n");

    polynomial *x,*y,*z;
    x=create_polynomial(a,8);
    y=create_polynomial(b,8);
    z=add_polynomial(x,y);

    list_for_each(&x->list,print_list,x);
    printf("\n");
    list_for_each(&y->list,print_list,y);
    printf("\n");
    list_for_each(&z->list,print_list,z);
}
