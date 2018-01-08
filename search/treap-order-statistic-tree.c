#include<stdio.h>
#include<stdlib.h>

typedef struct treap treap;
struct treap
{
    treap *left;
    treap *right;
    int prio;
    int data;
    int lsize,rsize;
};

static void set_size(treap *k)
{
    if(k!=NULL)
    {
        if(k->left)
            k->lsize=k->left->lsize+k->left->rsize+1;
        else
            k->lsize=0;
        if(k->right)
            k->rsize=k->right->lsize+k->right->rsize+1;
        else
            k->rsize=0;
    }
}

static treap* ll_rotate(treap *k2)
{
    treap *k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    set_size(k2);
    set_size(k1);
    return k1;
}

static treap* rr_rotate(treap *k2)
{
    treap *k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;
    set_size(k2);
    set_size(k1);
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
    else if(data>=r->data)
    {
        r->right=treap_add(r->right,data);
        if(r->right->prio<r->prio)
            r=rr_rotate(r);
    }
    else
    {

    }
    set_size(r);
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
            //their are the same elements ,it is different from the unique element version
            if(r->left->prio<r->right->prio)
            {
                r=ll_rotate(r);
                r->right=treap_del(r->right,data);
            }
            else
            {
                r=rr_rotate(r);
                r->left=treap_del(r->left,data);
            }
        }
    }
    set_size(r);
    return r;
}

int nth_x(treap *r,int i)
{
    int l=r->lsize+1;
    if(i==l)
        return r->data;
    else if(i<l)
        return nth_x(r->left,i);
    else
        return nth_x(r->right,i-l);
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
    for(int i=0;i<100000;i++)
        r=treap_add(r,rand());
    for(int i=100;i<900;i++)
    {
        printf("i=%d\n",i);
        r=treap_del(r,i);
    }
    r=treap_del(r,100);
    //r=treap_del(r,999);
    //r=treap_del(r,500);
    //inorder(r);
    //dfs(r,1);
    printf("%d %d\n",r->data,r->lsize+r->rsize+1);
    printf("%d",nth_x(r,50));
}
