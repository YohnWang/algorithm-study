#include<stdio.h>

void permutation(int a[],int isvisited[],int k,int n)
{
    static int array[1000];
    if(k==n)
    {
        for(int i=0;i<n;i++)
            printf("%d ",array[i]);
        printf("\n");
    }
    for(int i=0;i<n;i++)
    {
        if(isvisited[i]==0)
        {
            isvisited[i]=1;
            array[k]=a[i];
            permutation(a,isvisited,k+1,n);
            isvisited[i]=0;
        }
    }
}

int main(int argc,char *argv[])
{
    int a[]={1,2,3,4,5};
    int b[5]={0};
    permutation(a,b,0,5);
}
