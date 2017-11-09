#include<stdio.h>
#include<stdlib.h>

int bin_find(int a[],int n,int key)
{
    int begin=0,end=n-1;
    while(begin<=end)
    {
        int center=(begin+end)/2;
        if(a[center]==key)
            return center;
        else if(a[center]>key)
            end=center-1;
        else
            begin=center+1;
    }
    return -1;
}

int main(int argc,char *argv[])
{
    int a[]={0,1,2,3,4,5,6,7,8,9,10};
    printf("%d",bin_find(a,sizeof a/sizeof a[0],5));
}
