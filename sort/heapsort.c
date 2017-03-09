#include<stdio.h>

static inline int left(int i)
{
    return (i+1)*2-1;
}
static inline int right(int i)
{
    return (i+1)*2;
}
static inline int parent(int i)
{
    return (i-1)/2;
}

void heapify(int a[],int n,int i)
{
    int l=left(i);
    int r=right(i);
    int largest=i;
    if(l<n&&a[largest]<a[l])
        largest=l;
    if(r<n&&a[largest]<a[r])
        largest=r;
    if(largest!=i)
    {
        int tmp=a[i];
        a[i]=a[largest];
        a[largest]=tmp;
        heapify(a,n,largest);
    }
}

void make_heap(int a[],int n)
{
    for(int i=(n-1)/2;i>=0;i--)
        heapify(a,n,i);
}

int pop_heap(int a[],int n)
{
    int r=a[0];
    a[0]=a[n-1];
    heapify(a,n-1,0);
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
