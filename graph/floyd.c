#include<stdio.h>
#include<stdlib.h>

#define INF (1000000000) //one billion
#define NotAVertex (-1)

void init_graph(int n,int g[n][n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
                g[i][j]=0;
            else
                g[i][j]=INF;
        }
    }
}


void floyd(int n,int g[n][n],int d[n][n],int path[n][n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            d[i][j]=g[i][j];
            path[i][j]=-1;
        }
    }

    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                if(d[i][k]+d[k][j]<d[i][j])
                {
                    d[i][j]=d[i][k]+d[k][j];
                    path[i][j]=k;
                }
            }
}

void print_dist(int n,int d[n][n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%2d  ",d[i][j]);
        }
        printf("\n");
    }
}

void _print(int i,int j,int n,int path[n][n])
{
    if(path[i][j]==-1)
        printf("->%d",j);
    else
    {
        _print(i,path[i][j],n,path);
        printf("->%d",j);
    }
}

void print_path(int n,int path[n][n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i!=j)
            {
                printf("%d",i);
                _print(i,j,n,path);
                printf("\n");
            }
        }
    }
}

int main(int argc,char *argv[])
{
    int n=4;
    int g[n][n];
    init_graph(n,g);

    g[0][1]=2;
    g[0][2]=6;
    g[0][3]=4;
    g[1][2]=3;
    g[2][0]=7;
    g[2][3]=1;
    g[3][0]=5;
    g[3][2]=12;

    int d[n][n];
    int path[n][n];
    floyd(n,g,d,path);
    print_dist(n,d);
    print_path(n,path);
}
