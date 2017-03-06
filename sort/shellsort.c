#include<stdio.h>

void shell_insert(int a[],int n,int inc)
{
    for(int i=inc;i<n;i++)
    {
        int current=a[i];
        int j;
        for(j=i-inc;j>=0&&current<a[j];j-=inc)
            a[j+inc]=a[j];
        a[j+inc]=current;
    }
}

void shell_sort(int a[],int n)
{
    for(int i=n/2|1;i>1;i=i/2|1)
        shell_insert(a,n,i);
    shell_insert(a,n,1);
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
    shell_sort(a,sizeof a/sizeof a[0]);
    print_array(a,sizeof a/sizeof a[0]);
}
