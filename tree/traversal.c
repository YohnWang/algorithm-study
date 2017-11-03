#include<stdio.h>
#include<stdlib.h>

//iterative algorithm

typedef struct tree tree;
struct tree
{
    int data;
    tree *left;
    tree *right;
};

tree* make(int data,tree *left,tree *right)
{
    tree *p=malloc(sizeof(*p));
    p->left=left;
    p->right=right;
    p->data=data;
    return p;
}

tree* insert(tree *r,tree *left,tree *right)
{
    r->left=left;
    r->right=right;
    return r;
}

//a simple stack implement
typedef struct stack stack;
struct stack
{
    int capacity;
    int top;
    tree* space[];
};

stack *make_stack(int capacity)
{
    stack *s=malloc(sizeof(int)*2+capacity*sizeof(s->space[0]));
    s->capacity=capacity;
    s->top=0;
    return s;
}

void stack_push(stack *s,tree *node)
{
    int top=s->top;
    if(top<s->capacity)
        s->space[top]=node;
    s->top=top+1;
}

tree* stack_pop(stack *s)
{
    int top=s->top;
    if(top>0)
        top--;
    else
        return NULL;
    tree *r=s->space[top];
    s->top=top;
    return r;
}

tree* stack_top(stack *s)
{
    return s->space[s->top-1];
}


void pre_tra(tree *r)
{
    stack *s=make_stack(1024);
    if(r!=NULL)
        stack_push(s,r);
    while(s->top)
    {
        //the root node which should be visited
        tree *p=stack_pop(s);
        //visit until no left child
        while(p)
        {
             printf("%d ",p->data);
             stack_push(s,p);
             p=p->left;
        }
        //find the root of right subtree
        while(s->top&&p==NULL)
        {
            p=stack_pop(s);
            p=p->right;
        }
        //if p is NULL,there is no right subtree
        if(p!=NULL)
            stack_push(s,p);
    }
}

void inorder_tra(tree *r)
{
    stack *s=make_stack(1024);
    tree *p=r;
    stack_push(s,p);
    while(s->top)
    {
        //push the root of left subtree
        p=p->left;
        while(p)
        {
            stack_push(s,p);
            p=p->left;
        }
        //no left subtree,just visit until finding right subtree
        while(s->top&&p==NULL)
        {
            p=stack_pop(s);
            printf("%d ",p->data);
            p=p->right;
        }
        //push the root of right subtree
        if(p!=NULL)
            stack_push(s,p);
    }
}

void post_tra(tree *r)
{
    stack *s=make_stack(1024);
    tree *p=r;
    tree *last=NULL;
    //push all left node
    while(p)
    {
        stack_push(s,p);
        p=p->left;
    }
    while(s->top)
    {
        //check the top node ,visit or push its right sub
        p=stack_top(s);
        //the 'last' pointer mark the node's right subtree is visited
        if(p->right==NULL||p->right==last)
        {
            printf("%d ",p->data);
            last=p;
            stack_pop(s);
        }
        else
        {
            //if there are node unvisited,push this right subtree
            p=p->right;
            while(p)
            {
                stack_push(s,p);
                p=p->left;
            }
        }
    }
}

//a simple queue implement
typedef struct queue queue;
struct queue
{
    int front;
    int rear;
    int size;
    int capacity;
    tree* space[];
};

queue* make_queue(int capacity)
{
    queue *q=malloc(3*sizeof(int)+capacity*sizeof(q->space[0]));
    q->rear=0;
    q->front=0;
    q->capacity=capacity;
    q->size=0;
    return q;
}

void en_queue(queue *q,tree *node)
{
    int size=q->size;
    int capacity=q->capacity;
    if(size<capacity)
        size++;
    else
        return;
    int rear=q->rear;
    q->space[rear]=node;
    rear=(rear+1)%capacity;

    q->size=size;
    q->rear=rear;
}

tree* de_queue(queue *q)
{
    int size=q->size;
    if(size>0)
        size--;
    else
        return NULL;
    int front=q->front;
    tree *r=q->space[front];
    front=(front+1)%q->capacity;
    q->front=front;
    q->size=size;
    return r;
}

int is_empty(queue *q)
{
    if(q->size==0)
        return 1;
    else
        return 0;
}

void level_tra(tree *r)
{
    queue *q=make_queue(1024);
    if(r!=NULL)
        en_queue(q,r);
    while(!is_empty(q))
    {
        tree *p=de_queue(q);
        if(p->left)
            en_queue(q,p->left);
        if(p->right)
            en_queue(q,p->right);

        //visited operation,just print
        printf("%d ",p->data);
    }

}


tree* construct()
{
    tree *r=make(1,make(2,make(4,make(8,NULL,NULL)
                                 ,NULL)
                         ,make(5,NULL,NULL))
                 , make(3,make(6,NULL,NULL)
                          ,make(7,NULL,NULL))
                 );

    return r;
}

int main(int argc,char *argv[])
{
    //tree *r=make(1,make(3,make(6,NULL,NULL),NULL),make(2,make(4,NULL,NULL),make(5,NULL,NULL)));
    //tree *l=make(10,make(13,make(11,make(15,NULL,NULL),make(14,NULL,NULL)),NULL),make(12,NULL,NULL));
    //tree *h=make(20,r,l);
    tree *h=construct();
    level_tra(h);
    printf("\n");
    pre_tra(h);
    printf("\n");
    inorder_tra(h);
    printf("\n");
    post_tra(h);
}
