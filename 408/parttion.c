#include<stdio.h>
#include<stdlib.h>

//find the median

int parttion(int a[],int begin,int end,int n)
{
    if(begin==end)
        return begin;
    int v=a[begin];
    int i=begin,j=end+1;
    while(i<j)
    {
        while(i<=end&&a[++i]<v){}
        while(j>=begin&&a[--j]>v){} //'j>=begin' can be removed
        //swap
        if(i<j)
        {
            int tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
        }
    }
    a[begin]=a[j];
    a[j]=v;

    if(j<n/2)
        return parttion(a,j+1,end,n);
    else if(j>n/2)
        return parttion(a,begin,j-1,n);
    else
        return j;
}


int main(int argc,char *argv[])
{
    // [0,k-1] is A1
    // [k,n-1] is A2

    int a[]={4,1,9,8,3,5,6,7,2};
    int n=sizeof(a)/sizeof(a[0]);

    int k=parttion(a,0,n-1,n);
    printf("%d\n",k);
    for(int i=0;i<k;i++)
        printf("%d ",a[i]);
    printf("\n");
    for(int i=k;i<n;i++)
        printf("%d ",a[i]);
}
