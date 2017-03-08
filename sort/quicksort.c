#include<stdio.h>

/*
��������ĺ������ڻ��ֲ���
���л��ֵĲ����кܶ���
����ֻʵ�����е�һ��
ѡȡ��һ��Ԫ��Ϊ��Ŧ
���������ҵ���һ������Ŧ���Ԫ��
���������ҵ���һ������ŦС��Ԫ��
Ȼ�󽻻�����
ע�⵽��һ��Ԫ��Ϊ��Ŧ ����j���ղ���ָ����һ��Ԫ��֮ǰ ��i������ķ��� ��Ҫ���
�������ǰ�ߴ��ڵ��ں��� ��ô�������� �����˳�ѭ��
��ʱjָ���Ԫ����С����Ŧ�� ����Ŧ���� Ȼ����еݹ����


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
