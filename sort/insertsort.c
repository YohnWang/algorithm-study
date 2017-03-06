#include<stdio.h>
/*
���ڲ�������
��һ����ֱ�Ӳ������� �Ƚϼ�
�ڶ����ڵ�һ���Ļ����� �ı����Ե�Ѱ�Ҳ����Ĳ���
�����۰���������λ�� ��һ����Ҫ�������ϸ ��ȷ��Ѱ�ҵ��ĵ���������Ҫ�����λ��
�ò��Ĵ����д���� ��Ҫ��һЩʱ����֤
*/
void insert_sort(int a[],int n)
{
    for(int i=1;i<n;i++)
    {
        int j;
        int current=a[i];
        for(j=i-1;j>=0&&current<a[j];j--)
            a[j+1]=a[j];
        a[j+1]=current;
    }
}

void binary_insert_sort(int a[],int n)
{
    for(int i=1;i<n;i++)
    {
        int begin=0,end=i-1,mid;
        int current=a[i];
        while(begin<=end)
        {
            mid=(begin+end)/2;
            if(current<a[mid])
               end=mid-1;
            else
                begin=mid+1;
        }
        for(int j=i-1;j>end;j--)
            a[j+1]=a[j];
        a[end+1]=current;
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
    insert_sort(a,sizeof a/sizeof a[0]);
    print_array(a,sizeof a/sizeof a[0]);
    int b[]={5,7,9,8,2,1,6,4,3};
    binary_insert_sort(b,sizeof b/sizeof b[0]);
    print_array(b,sizeof b/sizeof b[0]);
}
