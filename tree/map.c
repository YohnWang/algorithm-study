#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
   char *key;
   int   value;
} Etype;

static int Etype_cmp(Etype *a,Etype *b)
{
    //
    return strcmp(a->key,b->key);
}

typedef struct avl avl;
struct avl
{
    avl *left;
    avl *right;
    int height;
    Etype data;
};

static inline int get_height(avl *r)
{
    if(r==NULL)
        return -1;
    return r->height;
}

static inline int max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}

static inline int max_height(avl *r1,avl *r2)
{
    return max(get_height(r1),get_height(r2));
}

static avl* ll_rotate(avl *k2)
{
    avl *k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    k2->height=max_height(k2->left,k2->right)+1;
    k1->height=max_height(k1->left,k1->right)+1;
    return k1;
}

static avl* rr_rotate(avl *k2)
{
    avl *k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;
    k2->height=max_height(k2->left,k2->right)+1;
    k1->height=max_height(k1->left,k1->right)+1;
    return k1;
}

static avl* lr_rotate(avl *k3)
{
    k3->left=rr_rotate(k3->left);
    return ll_rotate(k3);
}

static avl* rl_rotate(avl *k3)
{
    k3->right=ll_rotate(k3->right);
    return rr_rotate(k3);
}

avl* avl_add(avl *r,Etype x)
{
    if(r==NULL)
    {
        r=malloc(sizeof(*r));//allocation must be succeed
        if(r==NULL) {fprintf(stderr,"avl_add allocate faild\n");exit(1);}
        r->data=x;
        r->height=0;
        r->left=r->right=NULL;
        return r;
    }
    int cmp=Etype_cmp(&x,&r->data);

    if(cmp<0) //x<r->data
    {
        r->left=avl_add(r->left,x);
        int hl=get_height(r->left);
        int hr=get_height(r->right);
        if(hl-hr==2)
        {
            int cmp2=Etype_cmp(&x,&r->left->data);
            if(cmp2<0)
                r=ll_rotate(r);
            else
                r=lr_rotate(r);
        }
    }
    else if(cmp>0) //x>r->data
    {
        r->right=avl_add(r->right,x);
        int hl=get_height(r->left);
        int hr=get_height(r->right);
        if(hr-hl==2)
        {
            int cmp2=Etype_cmp(&x,&r->right->data);
            if(cmp2>0)
                r=rr_rotate(r);
            else
                r=rl_rotate(r);
        }
    }
    r->height=max_height(r->left,r->right)+1;
    return r;
}

typedef struct map map;
struct map
{
    avl *tree;
};

map* make_map()
{
    map *m=malloc(sizeof(*m));
    m->tree=NULL;
    return m;
}

void map_add(map *m,Etype x)
{
    m->tree=avl_add(m->tree,x);
}

int map_find(map *m,Etype key)
{
    avl *r=m->tree;
    while(r!=NULL)
    {
        int c=Etype_cmp(&key,&r->data);
        if(c==0)
            return r->data.value;
        else if(c<0)
            r=r->left;
        else
            r=r->right;
    }
    return -1;
}

int main(int argc,char *argv[])
{
    map *map=make_map();
    for(int i=0;i<100000;i++)
    {
        char *s=malloc(20);
        sprintf(s,"%d",i);
        Etype p={s,i};
        map_add(map,p);
    }
    printf("%d",map_find(map,(Etype){.key="100"}));
}
