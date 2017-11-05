#include<stdio.h>
#include<stdlib.h>



int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}
//ͳ���������еĺ� ����ʹ���0 �ͼ�����¼ �������¿�ʼ�ƺ�
//Ȼ��Ӽ�¼�ĺ���ѡ����
int search(int a[],int n)
{
    int sum[n];
    sum[0]=a[0]>0?a[0]:0;
    int M=sum[0];
    for(int i=1;i<n;i++)
    {
        sum[i]=max(sum[i-1]+a[i],a[i]);
        M=max(M,sum[i]);
    }
    return M;
}

int better_search(int a[],int n)
{
    int sum=0;
    sum=max(a[0],sum);
    int M=sum;
    for(int i=1;i<n;i++)
    {
        sum=max(sum+a[i],a[i]);
        M=max(M,sum);
    }
    return M;
}


int main(int argc,char *argv[])
{
    int a[]={1,3,-2,4,-5};
    printf("%d",better_search(a,5));
}
