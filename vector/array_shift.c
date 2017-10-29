#include<stdio.h>
#include<stdlib.h>


void rev(int a[],int begin,int end)
{
    int half=(end-begin)/2;
    for(int i=0;i<=half;i++)
    {
        int tmp=a[begin+i];
        a[begin+i]=a[end-i];
        a[end-i]=tmp;
    }
}

void shift(int a[],int n,int p)
{
    rev(a,0,p-1);
    rev(a,p,n-1);
    rev(a,0,n-1);
}

void print_array(int a[],int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
}

int main(int argc,char *argv[])
{
    int a[]={1,2,3,4,5,6,7,8,9};
    print_array(a,sizeof a/sizeof a[0]);
    shift(a,sizeof a/sizeof a[0],1);
    print_array(a,sizeof a/sizeof a[0]);
    shift(a,sizeof a/sizeof a[0],2);
    print_array(a,sizeof a/sizeof a[0]);
    shift(a,sizeof a/sizeof a[0],3);
    print_array(a,sizeof a/sizeof a[0]);
}
