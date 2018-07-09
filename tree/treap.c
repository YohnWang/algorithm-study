#include<stdio.h>
#include<stdlib.h>

typedef struct treap treap;
struct treap
{
    treap *left;
    treap *right;
    int prio;
    int data;
};

static treap* ll_rotate(treap *k2)
{
    treap *k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    return k1;
}

static treap* rr_rotate(treap *k2)
{
    treap *k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;
    return k1;
}
int quick_rand()
{
    static int seed=1;
    seed=seed*1103515245+12345;
    return seed;
}
treap* treap_add(treap *r,int data)
{
    if(r==NULL)
    {
        r=malloc(sizeof(*r));
        r->data=data;
        r->prio=quick_rand();
        r->left=NULL;
        r->right=NULL;
    }
    else if(data<r->data)
    {
        r->left=treap_add(r->left,data);
        if(r->left->prio<r->prio)
            r=ll_rotate(r);
    }
    else if(data>r->data)
    {
        r->right=treap_add(r->right,data);
        if(r->right->prio<r->prio)
            r=rr_rotate(r);
    }
    else
    {

    }
    return r;
}

treap* treap_del(treap *r,int data)
{
    if(r==NULL)
        return r;
    if(data<r->data)
        r->left=treap_del(r->left,data);
    else if(data>r->data)
        r->right=treap_del(r->right,data);
    else
    {
        if(r->left==NULL && r->right==NULL)
        {
            free(r);
            r=NULL;
        }
        else if(r->left==NULL)
        {
            treap *p=r->right;
            free(r);
            r=p;
        }
        else if(r->right==NULL)
        {
            treap *p=r->left;
            free(r);
            r=p;
        }
        else
        {
            if(r->left->prio<r->right->prio)
                r=ll_rotate(r);
            else
                r=rr_rotate(r);
            r=treap_del(r,data);
        }
    }
    return r;
}

void inorder(treap *r)
{
    if(r!=NULL)
    {
        inorder(r->left);
        printf("%d\n",r->data);
        inorder(r->right);
    }
}
int count=0;
void dfs(treap *r,int deep)
{
    if(r!=NULL)
    {
        if(deep>count)
            count=deep;
        dfs(r->left,deep+1);
        dfs(r->right,deep+1);
    }
}
int main(int argc,char *argv[])
{
    treap *r=NULL;
    for(int i=0;i<10000000;i++)
        r=treap_add(r,i);
    for(int i=100;i<900;i++)
        r=treap_del(r,i);
    // treap_del(r,0);
    // treap_del(r,999);
    // treap_del(r,500);
    //inorder(r);
    dfs(r,1);
    printf("%d",count);
}
