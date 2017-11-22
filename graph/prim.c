#include<stdio.h>
#include<stdlib.h>

#define INF (10000000)

struct vertex
{
    int n;
    int a[10];
    int w[10];
};
typedef struct vertex vertex;

void vertex_adj(vertex *v,int adj,int weight)
{
    v->a[v->n]=adj;
    v->w[v->n]=weight;
    v->n++;
}

int find_smallest(int n,int dist[],int visit[])
{
    int minx=INF,min=-1;
    for(int i=0;i<n;i++)
    {
        if(visit[i]==0&&dist[i]<minx)
        {
            minx=dist[i];
            min=i;
        }
    }
    return min;
}

void prim(vertex v[],int n,int d[],int path[],int edge[][2])
{
    int visit[n];
    for(int i=0;i<n;i++)
        visit[i]=0;
    d[0]=0;
    int count=0;
    for(;;)
    {
        int vx=find_smallest(n,d,visit);
        if(vx==-1)
            return ;
        visit[vx]=1;
        if(path[vx]!=-1)
        {
            edge[count][0]=path[vx];
            edge[count][1]=vx;
            count++;
        }
        for(int i=0;i<v[vx].n;i++)
        {
            int x=v[vx].a[i];
            if(v[vx].w[i]<d[x])
            {
                d[x]=v[vx].w[i];
                path[x]=vx;
            }
        }
    }
}
void print_edge(int edge[][2],int n)
{
    for(int i=0;i<n;i++)
        printf("%d--%d\n",edge[i][0],edge[i][1]);
}
int main(int argc,char *argv[])
{
    vertex v[10]={{0,{0},{0}}};
    int data[][3]={
        {0,1,2},
        {0,2,4},
        {0,3,1},
        {1,3,3},
        {1,4,10},
        {2,3,2},
        {2,5,5},
        {3,4,7},
        {3,5,8},
        {3,6,4},
        {4,6,6},
        {5,6,1},
    };
    for(int i=0;i<sizeof(data)/sizeof(data[0]);i++)
    {
        int u=data[i][0];
        int vx=data[i][1];
        int w=data[i][2];
        vertex_adj(&v[u],vx,w);
        vertex_adj(&v[vx],u,w);
    }
    int d[7]={[0 ... 6]=INF};
    int path[7]={[0 ... 6]=-1};
    int edge[6][2];
    prim(v,7,d,path,edge);
    print_edge(edge,6);
}
