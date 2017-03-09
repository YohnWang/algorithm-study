#include<stdio.h>

void select_sort(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        int min=i;
        for(int j=i+1;j<n;j++)
            if(a[min]>a[j])
                min=j;
        int tmp=a[min];
        a[min]=a[i];
        a[i]=tmp;
    }
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
    select_sort(a,sizeof a/sizeof a[0]);
    print_array(a,sizeof a/sizeof a[0]);
}
