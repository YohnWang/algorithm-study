#include<stdio.h>
#include<stdlib.h>

//iterative implement

void percdown(int a[],int i,int n)
{
    //percolate down node i
    for(;i<n;)
    {
        int left=2*i+1;
        int right=left+1;
        int largest=i;
        if(left<n&&a[largest]<a[left])
            largest=left;
        if(right<n&&a[largest]<a[right])
            largest=right;
        if(largest!=i)
        {
            int tmp=a[i];
            a[i]=a[largest];
            a[largest]=tmp;
            i=largest;
        }
        else
        {
            break;
        }
    }
}

void make_heap(int a[],int n)
{
    for(int i=(n-1)/2;i>=0;i--)
        percdown(a,i,n);
}

int pop_heap(int a[],int n)
{
    int r=a[0];
    a[0]=a[n-1];
    percdown(a,0,n-1);
    a[n-1]=r;
    return r;
}

void heap_sort(int a[],int n)
{
    make_heap(a,n);
    for(int i=n;i>0;i--)
        pop_heap(a,i);
}
void print_array(int a[],int n)
{
    if(n>0)
        printf("%d",a[0]);
    for(int i=1;i<n;i++)
        printf(" %d",a[i]);
    printf("\n");
}
int main(int argc,char *argv[])
{
    int a[]={5,7,9,8,2,1,6,4,3};
    heap_sort(a,sizeof a/sizeof a[0]);
    print_array(a,sizeof a/sizeof a[0]);
}
