#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

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

//graph
typedef struct vertex vertex;
struct vertex
{
    vector adj;
    vector weight;
};

vertex* vertex_init(vertex *v,int id)
{
    vector_init(&v->adj);
    vector_init(&v->weight);
    return v;
}

void vertex_adj(vertex *v,int n,...)
{
    va_list args;
    va_start(args,n);
    for(int i=0;i<n;i++)
    {
        int adj=va_arg(args,int);
        int w=va_arg(args,int);
        vector_push_back(&v->adj,adj);
        vector_push_back(&v->weight,w);
    }
    va_end(args);
}

int find_smallest(int n,int dist[],int path[],int visit[])
{
    int minx,min;
    for(min=0;min<n&&visit[min]==1;min++){}
    if(min==n)
        return -1;
    minx=dist[min];
    for(int i=min+1;i<n;i++)
    {
        if(visit[i]!=1&&dist[i]!=-1&&dist[i]<minx)
        {
            min=i;
            minx=dist[min];
        }
    }
    return min;
}

void dijkstra(vertex vertex[],int n,int source,int dist[],int path[])
{
    int visit[n];
    memset(visit,0,n*sizeof(int));
    int v=source;
    dist[v]=0;
    for( ;;)
    {
        v=find_smallest(n,dist,path,visit);
        if(v==-1)
            return ;
        visit[v]=1;
        for(int i=0;i<vector_size(&vertex[v].adj);i++)
        {
            int vx=vector_at(&vertex[v].adj,i);
            int w=vector_at(&vertex[v].weight,i);
            if(dist[vx]==-1 || dist[v]+w<dist[vx])
            {
                dist[vx]=dist[v]+w;
                path[vx]=v;
            }
        }
    }
}

void print_path(int path[],int i)
{
    if(path[i]==-1)
        printf("source");
    else
    {
        print_path(path,path[i]);
        printf("->%d",i);
    }
}

void print_result(vertex v[],int n,int dist[],int path[])
{
    for(int i=0;i<n;i++)
    {
        printf("id=%d ",i);
        print_path(path,i);
        printf("\n");
    }
}

int main(int argc,char *argv[])
{
    vertex v[10];
    for(int i=0;i<7;i++)
    {
        vertex_init(&v[i],i);
    }
    vertex_adj(&v[0],2,1,2,3,1);
    vertex_adj(&v[1],2,3,3,4,10);
    vertex_adj(&v[2],2,0,4,5,5);
    vertex_adj(&v[3],3,2,2,5,8,6,4,4,2);
    vertex_adj(&v[4],1,6,6);
    vertex_adj(&v[5],0);
    vertex_adj(&v[6],1,5,1);

    int dist[10]={[0 ... 9]=-1};
    int path[10]={[0 ... 9]=-1};
    dijkstra(v,7,0,dist,path);
    print_result(v,7,dist,path);
}
