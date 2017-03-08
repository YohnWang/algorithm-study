#include<stdio.h>

/*
快速排序的核心在于划分步骤
其中划分的策略有很多种
这里只实现其中的一种
选取第一个元素为枢纽
从左至右找到第一个比枢纽大的元素
从右至左找到第一个比枢纽小的元素
然后交换二者
注意到第一个元素为枢纽 所以j最终不会指到第一个元素之前 而i有溢出的风险 需要检测
如果坐标前者大于等于后者 那么不做交换 并且退出循环
此时j指向的元素是小于枢纽的 与枢纽交换 然后进行递归调用


*/

void _quick_sort(int a[],int begin,int end)
{
    if(begin>=end)
        return;
    int pivot=a[begin];
    int i=begin,j=end+1;
    while(i<j)
    {
        while(i<end&&a[++i]<pivot){}
        while(a[--j]>pivot){}
        if(i<j)
        {
            int tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
        }
    }
    a[begin]=a[j];
    a[j]=pivot;
    _quick_sort(a,begin,j-1);
    _quick_sort(a,j+1,end);
}

static inline void quick_sort(int a[],int n)
{
    _quick_sort(a,0,n-1);
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
    quick_sort(a,sizeof a/sizeof a[0]);
    print_array(a,sizeof a/sizeof a[0]);

}
