#include<stdio.h>

int max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}
static int c[1000][1000];
int lcs_length(int a[],int an,int b[],int bn)
{
    for(int i=0;i<an;i++)
    {
        for(int j=0;j<bn;j++)
        {
            if(a[i]==b[j])
            {
                c[i+1][j+1]=c[i][j]+1;
            }
            else
            {
                c[i+1][j+1]=max(c[i][j+1],c[i+1][j]);
            }
        }
    }
    /*
    for(int i=0;i<=an;i++)
    {
        for(int j=0;j<=bn;j++)
        {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    */
    return c[an][bn];

}

int main(int argc,char *argv[])
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int b[5]={1,2,10,7,9};
    printf("%d\n",lcs_length(a,10,b,5));
}
