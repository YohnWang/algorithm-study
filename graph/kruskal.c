#include<stdio.h>
#include<stdlib.h>

struct set
{
    int n;
    int a[];
};
typedef struct set set;

set* make_set(int size)
{
    set *s=malloc(sizeof(*s)+size*sizeof(int));
    s->n=size;
    for(int i=0;i<size;i++)
        s->a[i]=-1;
    return s;
}

int find(set *s,int x)
{
    if(s->a[x]<0)
        return x;
    else
        return s->a[x]=find(s,s->a[x]);
}

void set_union(set *s,int a,int b)
{
    int r1=find(s,a);
    int r2=find(s,b);
    s->a[r1]=r2;
}

struct edge
{
    int weight;
    int u,v;
};
typedef struct edge edge;

void set_edge(edge *e,int u,int v,int w)
{
    e->u=u;
    e->v=v;
    e->weight=w;
}

int comp(const void *aa,const void *bb)
{
    const edge *a=aa,*b=bb;
    return a->weight-b->weight;
}

int kruskal(edge e[],int n,int vn,int result[])
{
    qsort(e,n,sizeof(e[0]),comp);
    int edge_accepted=0;
    set *s=make_set(vn);
    for(int i=0;edge_accepted<vn-1&&i<n;i++)
    {
        int u=e[i].u;
        int v=e[i].v;
        int uset=find(s,u);
        int vset=find(s,v);
        if(uset!=vset)
        {
            result[edge_accepted]=i;
            edge_accepted++;

            set_union(s,uset,vset);
        }
    }
    return edge_accepted;
}

int main(int argc,char *argv[])
{
    edge e[100];
    set_edge(&e[0],0,1,2);
    set_edge(&e[1],0,2,4);
    set_edge(&e[2],0,3,1);
    set_edge(&e[3],1,3,3);
    set_edge(&e[4],1,4,10);
    set_edge(&e[5],2,3,2);
    set_edge(&e[6],2,5,5);
    set_edge(&e[7],3,4,7);
    set_edge(&e[8],3,5,8);
    set_edge(&e[9],3,6,4);
    set_edge(&e[10],4,6,6);
    set_edge(&e[11],5,6,1);
    int n=12,vn=7;
    int r[7];
    kruskal(e,n,vn,r);
    for(int i=0;i<vn-1;i++)
    {
        int k=r[i];
        printf("%d--%d\n",e[k].u,e[k].v);
    }
}
