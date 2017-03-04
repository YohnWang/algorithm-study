#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
//vector type of unsigned char
typedef signed char Etype;

struct vector
{
    int size;
    int capacity;
    Etype *a;
};
typedef struct vector vector;

vector* vector_init(vector *v)
{
    v->size=0;
    v->capacity=2;
    v->a=malloc(v->capacity*sizeof(Etype));
    if(v->a==NULL)
        return NULL;
    return v;
}

void vector_del(vector *v)
{
    v->size=0;
    v->capacity=0;
    free(v->a);
    v->a=NULL;
}

void vector_push_back(vector *v,Etype e)
{
    if(v->size==v->capacity)
    {
        v->capacity+=v->capacity;
        Etype *replace=malloc(v->capacity*sizeof(Etype));
        memcpy(replace,v->a,v->size*sizeof(Etype));
        free(v->a);
        v->a=replace;
    }
    v->a[v->size++]=e;
}

void vector_pop_back(vector *v)
{
    if(v->size)
        v->size--;
}

Etype vector_at(vector *v,int position)
{
    return v->a[position];
}

int vector_size(vector *v)
{
    return v->size;
}

void vector_copy(vector *new,vector *v)
{
    new->size=v->size;
    new->capacity=v->capacity;
    new->a=malloc(new->capacity*sizeof(Etype));
    memcpy(new->a,v->a,new->size*sizeof(Etype));
}

//big number
typedef struct bgn bgn;
struct bgn
{
    char sign;
    vector v;
};

int bgn_assert(const char s[])
{
    int i;
    for(i=0;s[i]!='\0';i++)
    {
        if(isdigit(s[i])||(i==0&&(s[i]=='+'||s[i]=='-')))
            continue;
        else
            return 0;
    }
    return i;
}

bgn bgn_new(const char s[])
{
    char s_end=bgn_assert(s);
    if(s_end==0)
        return bgn_new("0");
    else
    {
        bgn r;
        vector_init(&r.v);
        int begin=0,end=s_end-1;
        if(s[begin]=='-')
        {
            r.sign=1;
            begin++;
        }
        else if(s[begin]=='+')
        {
            r.sign=0;
            begin++;
        }
        else
            r.sign=0;
        while(s[begin]=='0'){begin++;}
        if(begin>end)
        {
            r.sign=0;
            vector_push_back(&r.v,0);
        }
        for(;end>=begin;end--)
        {
            vector_push_back(&r.v,s[end]-'0');
        }
        return r;
    }
}

void bgn_del(bgn b)
{
    vector_del(&b.v);
}

char* bgn_str(char *s,bgn b)
{
    int i,k=0;
    if(b.sign)
        s[k++]='-';
    for(int i=b.v.size-1;i>=0;i--)
        s[k++]=b.v.a[i]+'0';
    s[k]='\0';
    return s;
}

bgn bgn_neg(bgn b) //notice ,return element is the b itself,do not change it or use it after change original b
{
    b.sign=!b.sign;
    return b;
}

int bgn_cmp(bgn a,bgn b)
{
    if(a.sign==0&&b.sign)
        return 1;
    else if(a.sign&&b.sign==0)
        return -1;
    else if(a.sign&&b.sign)
        return -bgn_cmp(bgn_neg(a),bgn_neg(b));
    if(a.v.size>b.v.size)
        return 1;
    else if(a.v.size<b.v.size)
        return -1;
    for(int i=a.v.size-1;i>=0;i--)
    {
        if(a.v.a[i]>b.v.a[i])
            return 1;
        else if(a.v.a[i]<b.v.a[i])
            return -1;
    }
    return 0;
}

bgn bgn_sub(bgn a,bgn b);
bgn bgn_add(bgn a,bgn b)
{
    bgn c;
    int i=0,j=0;
    if(a.sign&&b.sign)
        c.sign=1;
    else if(a.sign&&b.sign==0)
        return bgn_sub(b,bgn_neg(a));
    else if(a.sign==0&&b.sign)
        return bgn_sub(a,bgn_neg(b));
    else
        c.sign=0;

    int carry=0;
    vector_init(&c.v);
    while(i<a.v.size && j<b.v.size)
    {
        int sum=a.v.a[i]+b.v.a[j]+carry;
        vector_push_back(&c.v,sum%10);
        carry=sum/10;
        i++;j++;
    }
    while(i<a.v.size)
    {
        int sum=a.v.a[i]+carry;
        vector_push_back(&c.v,sum%10);
        carry=sum/10;
        i++;
    }
    while(j<b.v.size)
    {
        int sum=b.v.a[j]+carry;
        vector_push_back(&c.v,sum%10);
        carry=sum/10;
        j++;
    }
    if(carry!=0)
        vector_push_back(&c.v,carry);
    return c;
}

bgn bgn_sub(bgn a,bgn b)
{
    bgn c;
    if(a.sign==0&&b.sign)// 1-(-1)
        return bgn_add(a,bgn_neg(b));
    else if(a.sign&&b.sign==0)//(-1)-1
    {
        c=bgn_add(bgn_neg(a),b);
        c.sign=1;
        return c;
    }
    else if(a.sign&&b.sign)//(-1)-(-1)
        return bgn_add(a,bgn_neg(b));
    // 1-1
    int cmp=bgn_cmp(a,b);
    if(cmp==0)
        return bgn_new("0");
    else if(cmp==-1)
        return bgn_neg(bgn_sub(b,a));
    int carry=0;
    int i=0,j=0;
    vector_init(&c.v);
    c.sign=0;
    while(i<a.v.size && j<b.v.size)
    {
        int diff=a.v.a[i]-b.v.a[j]-carry;
        if(diff<0)
        {
            diff+=10;
            carry=1;
        }
        else
            carry=0;
        vector_push_back(&c.v,diff);
        i++;j++;
    }
    while(i<a.v.size)
    {
        int diff=a.v.a[i]-carry;
        carry=0;
        vector_push_back(&c.v,diff);
        i++;
    }
    return c;
}


int main(int argc,char *argv[])
{
    char s[100];
    bgn a,b;
    a=bgn_new("-0");
    b=bgn_new("0");
    bgn c=bgn_add(a,b);
    printf("%s\n",bgn_str(s,a));
}
