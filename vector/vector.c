#include<stdlib.h>
#include<string.h>
typedef int Etype;

struct vector
{
    int size;
    int capacity;
    Etype *a;
};
typedef struct vector vector;

vector* vector_init(vector *v)
{
    v->size=0;
    v->capacity=2;
    v->a=malloc(v->capacity*sizeof(Etype));
    if(v->a==NULL)
        return NULL;
    return v;
}

void vector_del(vector *v)
{
    v->size=0;
    v->capacity=0;
    free(v->a);
    v->a=NULL;
}

void vector_push_back(vector *v,Etype e)
{
    if(v->size==v->capacity)
    {
        v->capacity+=v->capacity;
        Etype *replace=malloc(v->capacity*sizeof(Etype));
        memcpy(replace,v->a,v->size*sizeof(Etype));
        free(v->a);
        v->a=replace;
    }
    v->a[v->size++]=e;
}

void vector_pop_back(vector *v)
{
    if(v->size)
        v->size--;
}

Etype vector_at(vector *v,int position)
{
    return v->a[position];
}

int vector_size(vector *v)
{
    return v->size;
}

void vector_copy(vector *new,vector *v)
{
    new->size=v->size;
    new->capacity=v->capacity;
    new->a=malloc(new->capacity*sizeof(Etype));
    memcpy(new->a,v->a,new->size*sizeof(Etype));
}

#include<stdio.h>
int main(int argc,char *argv[])
{
    vector v;
    vector_init(&v);
    for(int i=0;i<4000;i++)
        vector_push_back(&v,i);
    vector vx;
    vector_copy(&vx,&v);
    for(int i=0;i<vx.size;i++)
        printf("%d\n",vector_at(&vx,i));
    vector_del(&v);
}
