#include<stdio.h>
int max(int a,int b)
{
    if(a<b)
        return b;
    else
        return a;
}
int cut_rod(int p[],int n,int r[])
{
    if(r[n]!=0)
        return r[n];
    if(n==0)
        return 0;
    int q=p[0];
    for(int i=1;i<=n;i++)
        q=max(q,p[i]+cut_rod(p,n-i,r));
    r[n]=q;
    return q;
}
int main(int argc,char *argv[])
{
    int p[11]={0,1,5,8,9,10,17,17,20,24,30};
    int n=10;
    int r[n+1];
    for(int i=0;i<n+1;i++)
        r[i]=0;
    printf("%d",cut_rod(p,n,r));

}
