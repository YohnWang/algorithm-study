#include<stdio.h>
#include<stdlib.h>

struct node
{
    int left;
    int right;
    int count;
};

struct bost
{
    struct node *v;
    int range;
};
typedef struct bost bost;

bost make_bost(int range)
{
    bost b;
    b.v=malloc(sizeof(b.v[0])*(range+1));
    b.range=range;
    for(int i=0;i<=range;i++)
    {
        b.v[i].count=0;
        b.v[i].left=0;
        b.v[i].right=0;
    }
    return b;
}

void push(bost *b,int x)
{
    int left=0,right=b->range;
    while(left<=right)
    {
        int center=(left+right)/2;
        if(x<center)
        {
            b->v[center].left++;
            right=center-1;
        }
        else if(x>center)
        {
            b->v[center].right++;
            left=center+1;
        }
        else
        {
            b->v[center].count++;
            break;
        }
    }
}

int exist(bost *b,int x)
{
    if(b->v[x].count>0)
        return 1;
    return 0;
}

int erase(bost *b,int x)
{
    if(exist(b,x)==0)
        return 0;
    int left=0,right=b->range;
    while(left<=right)
    {
        int center=(left+right)/2;
        if(x<center)
        {
            b->v[center].left--;
            right=center-1;
        }
        else if(x>center)
        {
            b->v[center].right--;
            left=center+1;
        }
        else
        {
            b->v[center].count--;
            break;
        }
    }
    return 1;
}

int nth_x(bost *b,int i)
{
    int left=0,right=b->range;
    int center=(left+right)/2;
    while(left<=right)
    {
        center=(left+right)/2;
        int l=b->v[center].left;
        int c=b->v[center].count;
        if(i<=l)
            right=center-1;
        else if(i>l+c)
        {
            i=i-l-c;
            left=center+1;
        }
        else
            return center;
    }
    return center;
}

int main(int argc,char *argv[])
{
    bost b=make_bost(1000);
    for(int i=0;i<100;i++)
    {
        push(&b,i);
        push(&b,i);
    }
    printf("%d",nth_x(&b,50));
}
