#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

//vector
typedef struct vertex vertex;
typedef vertex* Etype;

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

//graph

struct vertex
{
    int id;
    vector adjacent_vertex;
};

vertex* vertex_init(vertex *v,int id)
{
    v->id=id;
    vector_init(&v->adjacent_vertex);
    return v;
}

void vertex_adj(vertex *v,int n,...)
{
    va_list args;
    va_start(args,n);
    for(int i=0;i<n;i++)
    {
        vertex *vx=va_arg(args,vertex*);
        vector_push_back(&v->adjacent_vertex,vx);
    }
    va_end(args);
}

void find_shortest_path(vertex v[],int n,vertex *s,int distance[],vertex* path[])
{
    distance[s->id]=0;
    path[s->id]=NULL;
    vertex* queue[n+1];
    int front=0,rear=0;
    queue[rear++]=s;
    while(front!=rear)
    {
        vertex *vx=queue[front++];

        for(int i=0;i<vx->adjacent_vertex.size;i++)
        {
            vertex *x=vector_at(&vx->adjacent_vertex,i);
            if(distance[x->id]<0)
            {
                distance[x->id]=distance[vx->id]+1;
                path[x->id]=vx;
                queue[rear++]=x;
            }
        }
    }
}

void print_path(vertex* path[],vertex *vx)
{
    if(path[vx->id]==NULL)
        printf("source");
    else
    {
        print_path(path,path[vx->id]);
        printf("->%d",vx->id);
    }
}

void print_result(vertex v[],int n,int dist[],vertex* path[])
{
    for(int i=1;i<=n;i++)
    {
        printf("id=%d ",v[i].id);
        print_path(path,&v[i]);
        printf("\n");
    }
}

int main(int argc,char *argv[])
{
    vertex v[10];
    for(int i=1;i<=7;i++)
    {
        vertex_init(&v[i],i);
    }
    vertex_adj(&v[1],2,&v[2],&v[4]);
    vertex_adj(&v[2],2,&v[4],&v[5]);
    vertex_adj(&v[3],2,&v[1],&v[6]);
    vertex_adj(&v[4],3,&v[3],&v[6],&v[7]);
    vertex_adj(&v[5],1,&v[7]);
    vertex_adj(&v[6],0);
    vertex_adj(&v[7],1,&v[6]);

    int dist[10]={[0 ... 9]=-1};
    vertex* path[10];
    find_shortest_path(v,7,&v[3],dist,path);
    print_result(v,7,dist,path);
}
