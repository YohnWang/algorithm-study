#include<stdio.h>
#include<stdlib.h>

void merge(int a[],int tmp[],int begin,int mid,int end)
{
    int l=begin,r=mid+1;
    int cnt=begin;
    while(l<=mid && r<=end)
    {
        if(a[l]<a[r])
            tmp[cnt++]=a[l++];
        else
            tmp[cnt++]=a[r++];
    }
    while(l<=mid)
        tmp[cnt++]=a[l++];
    while(r<=end)
        tmp[cnt++]=a[r++];
    for(int i=begin;i<=end;i++)
        a[i]=tmp[i];
}

void _merge_sort(int a[],int tmp[],int begin,int end)
{
    if(begin==end)
        return ;
    int mid=(begin+end)/2;
    _merge_sort(a,tmp,begin,mid);
    _merge_sort(a,tmp,mid+1,end);
    merge(a,tmp,begin,mid,end);
}

void merge_sort(int a[],int n)
{
    int tmp[n];
    _merge_sort(a,tmp,0,n-1);
}

void print_array(int a[],int n)
{
    if(n>0)
        printf("%d",a[0]);
    for(int i=1;i<n;i++)
        printf(" %d",a[i]);
    printf("\n");
}

int main()
{
    int a[]={5,7,9,8,2,1,6,4,3};
    merge_sort(a,sizeof a/sizeof a[0]);
    print_array(a,sizeof a/sizeof a[0]);
}
