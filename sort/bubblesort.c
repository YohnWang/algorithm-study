#include<stdio.h>

/*
这里的冒泡排序策略是第一个与第二个比较 第二个与第三个...依次类推
另外还有其他的冒泡策略 比如第一个与第二个 第一个与第三个 ...
这里只给出第一种
*/

void bubble_sort(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                int tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
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
    bubble_sort(a,sizeof a/sizeof a[0]);
    print_array(a,sizeof a/sizeof a[0]);

}
