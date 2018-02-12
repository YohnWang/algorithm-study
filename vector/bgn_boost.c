#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdint.h>

//data structure of vector
typedef int32_t Etype;

struct vector
{
    int size;
    int capacity;
    Etype *a;
};
typedef struct vector vector;

//vector information
static inline int vector_size(vector *v)
{
    return v->size;
}

static inline int vector_capacity(vector *v)
{
    return v->capacity;
}

//resource management

static void vector_recapacity(vector *v,int new_cap)
{
    int cap=vector_capacity(v);
    int size=vector_size(v);
    //only when new_cap>cap can change capacity
    if(new_cap>cap)
    {
        Etype *p=malloc(new_cap*sizeof(Etype));
        //add exception
        memcpy(p,v->a,size*sizeof(Etype));
        free(v->a);
        v->capacity=new_cap;
        v->a=p;
    }
}

static void vector_resize(vector *v,int new_size)
{
    int size=vector_size(v);
    if(size<new_size)
    {
        int cap=vector_capacity(v);
        if(new_size<cap)
            v->size=new_size;
        else
        {
            vector_recapacity(v,new_size);
            v->size=new_size;
        }
    }
}

//vector interface

vector* vector_init(vector *v)
{
    v->size=0;
    v->capacity=0;
    v->a=NULL;
    return v;
}

void vector_del(vector *v)
{
    v->size=0;
    v->capacity=1;
    free(v->a);
    v->a=NULL;
}

static void vector_push_back(vector *v,Etype e)
{
    int size=vector_size(v);
    int cap =vector_capacity(v);
    if(size==cap)
        vector_recapacity(v,(cap<<2)+1);
    v->a[v->size++]=e;
}

static void vector_pop_back(vector *v)
{
    if(v->size!=0)
        v->size--;
}

static inline Etype* vector_at(vector *v,int position)
{
    return &v->a[position];
}

static inline Etype* vector_back(vector *v)
{
    return &v->a[v->size-1];
}

void vector_copy(vector *new,vector *v)
{
    new->size=v->size;
    new->capacity=v->capacity;
    new->a=malloc(new->capacity*sizeof(Etype));
    memcpy(new->a,v->a,new->size*sizeof(Etype));
}



//big number
enum {POSITIVE,NEGATIVE,RADIX=1000000000};
typedef struct bgn bgn;
struct bgn
{
    int sign;
    vector v;
};

bgn bgn_new(int32_t integer)
{
    bgn r;
    if(integer>=0)
        r.sign=POSITIVE;
    else
        r.sign=NEGATIVE;
    vector_init(&r.v);
    vector_push_back(&r.v,abs(integer));
    //if(abs(integer)>=RADIX)
    //    vector_push_back(&r->v,1);
    return r;
}

void bgn_del(bgn b)
{
    vector_del(&b.v);
}

char* bgn_str(char *s,bgn b)
{
    char tmp[64];
    if(b.sign==NEGATIVE)
        sprintf(tmp,"-%d",*vector_back(&b.v));
    else
        sprintf(tmp,"%d",*vector_back(&b.v));
    strcpy(s,tmp);
    for(int i=vector_size(&b.v)-2;i>=0;i--)
    {
        sprintf(tmp,"%.9d",*vector_at(&b.v,i));
        strcat(s,tmp);
    }
    return s;
}

bgn* bgn_neg(bgn *b)
{
    if(b->sign==POSITIVE)
        b->sign=NEGATIVE;
    else
        b->sign=POSITIVE;
    return b;
}

static int bgn_cmp_ls_pos(bgn a,bgn b)
{
    int len=vector_size(&a.v);
    for(int i=len-1;i>=0;i--)
    {
        if(*vector_at(&a.v,i)>*vector_at(&b.v,i))
            return 1;
        else if(*vector_at(&a.v,i)<*vector_at(&b.v,i))
            return -1;
    }
    return 0;
}

static int bgn_cmp_nosign(bgn a,bgn b)
{
    int alen=vector_size(&a.v);
    int blen=vector_size(&b.v);
    if(alen>blen)
        return 1;
    else if(alen<blen)
        return -1;
    else
        return bgn_cmp_ls_pos(a,b);
}

int bgn_cmp(bgn a,bgn b)
{
    if(a.sign==POSITIVE&&b.sign==POSITIVE)
        return bgn_cmp_nosign(a,b);
    else if(a.sign==NEGATIVE&&b.sign==NEGATIVE)
        return -bgn_cmp_nosign(a,b);
    else if(a.sign==POSITIVE&&b.sign==NEGATIVE)
        return 1;//>
    else
        return -1;//<
}

static bgn bgn_add_nosign(bgn a,bgn b)
{
    bgn c=bgn_new(0);
    vector_pop_back(&c.v);
    int cap=vector_size(&a.v)>vector_size(&b.v)?vector_size(&a.v):vector_size(&b.v);
    vector_recapacity(&c.v,cap+1);
    int i;
    int32_t carry=0;
    for(i=0;i<vector_size(&a.v)&&i<vector_size(&b.v);i++)
    {
        int32_t sum=*vector_at(&a.v,i)+*vector_at(&b.v,i)+carry;
        carry=sum/RADIX;
        vector_push_back(&c.v,sum%RADIX);
    }
    if(i<vector_size(&a.v))
    {
        int32_t sum=*vector_at(&a.v,i)+carry;
        vector_push_back(&c.v,sum);
        carry=0;
        i++;
    }
    while(i<vector_size(&a.v))
        vector_push_back(&c.v,*vector_at(&a.v,i++));
    if(i<vector_size(&b.v))
    {
        int32_t sum=*vector_at(&b.v,i)+carry;
        vector_push_back(&c.v,sum);
        carry=0;
        i++;
    }
    while(i<vector_size(&b.v))
        vector_push_back(&c.v,*vector_at(&b.v,i++));
    if(carry!=0)
        vector_push_back(&c.v,carry);
    return c;
}

static bgn bgn_sub_nosign_bg(bgn a, bgn b) //a>b
{
    bgn c=bgn_new(0);
    vector_pop_back(&c.v);
    int32_t carry=0;
    int i;
    for(i=0;i<vector_size(&b.v);i++)
    {
        int diff=*vector_at(&a.v,i)-*vector_at(&b.v,i)-carry;
        if(diff<0)
        {
            diff+=RADIX;
            carry=1;
        }
        else
            carry=0;
        vector_push_back(&c.v,diff);
    }
    if(i<vector_size(&a.v))
    {
        int diff=*vector_at(&a.v,i)-*vector_at(&b.v,i)-carry;
        if(diff<0)
        {
            diff+=RADIX;
            carry=1;
        }
        else
            carry=0;
        vector_push_back(&c.v,diff);
        i++;
    }
    while(i<vector_size(&a.v))
        vector_push_back(&c.v,*vector_at(&a.v,i++));
    while(*vector_back(&c.v)==0)
        vector_pop_back(&c.v);
    return c;
}

static bgn bgn_sub_nosign(bgn a,bgn b)
{
    int cmp=bgn_cmp_nosign(a,b);
    if(cmp>0)
    {
         bgn c=bgn_sub_nosign_bg(a,b);
         c.sign=POSITIVE;
         return c;
    }
    else if(cmp<0)
    {
        bgn c=bgn_sub_nosign_bg(b,a);
        c.sign=NEGATIVE;
        return c;
    }
    else
        return bgn_new(0);
}

bgn bgn_sub(bgn a, bgn b);
bgn bgn_add(bgn a,bgn b)
{
    bgn c;
    if(a.sign==b.sign)
    {
        c=bgn_add_nosign(a,b);
        c.sign=a.sign;
    }
    else if(a.sign==POSITIVE)
    {
        bgn_neg(&b);
        c=bgn_sub(a,b);
        bgn_neg(&b);
    }
    else
    {
        bgn_neg(&a);
        c=bgn_sub(b,a);
        bgn_neg(&a);
    }
    return c;
}

bgn bgn_sub(bgn a,bgn b)
{
    bgn c;
    if(a.sign==POSITIVE&&b.sign==POSITIVE)
    {
        c=bgn_sub_nosign(a,b);
    }
    else if(a.sign==NEGATIVE&&b.sign==NEGATIVE)
    {
        c=bgn_sub_nosign(a,b);
        bgn_neg(&c);
    }
    else if(a.sign==POSITIVE)
    {
        bgn_neg(&b);
        c=bgn_add(a,b);
        bgn_neg(&b);
    }
    else
    {
        bgn_neg(&a);
        c=bgn_add(a,b);
        bgn_neg(&a);
    }
    return c;
}

bgn bgn_sl(bgn b,int offset)
{
    bgn c=bgn_new(0);
    vector_pop_back(&c.v);
    vector_recapacity(&c.v,vector_size(&c.v)+offset+1);
    c.sign=b.sign;
    for(int i=0;i<offset;i++)
        vector_push_back(&c.v,0);
    for(int i=0;i<vector_size(&b.v);i++)
        vector_push_back(&c.v,*vector_at(&b.v,i));
    return c;
}

bgn bgn_sr(bgn b,int offset)
{
    if(offset>=vector_size(&b.v))
        return bgn_new(0);
    bgn c=bgn_new(0);
    vector_pop_back(&c.v);
    vector_recapacity(&c.v,vector_size(&c.v)-offset+1);
    c.sign=b.sign;
    for(int i=offset;i<vector_size(&b.v);i++)
        vector_push_back(&c.v,*vector_at(&b.v,i));
    return c;
}

bgn bgn_shift(bgn b,int offset)
{


   // return c;
}

static bgn bgn_mul_nor(bgn a,bgn b)
{
    bgn c=bgn_new(0);
    vector_pop_back(&c.v);
    for(int i=0;i<vector_size(&a.v);i++)
    {
        bgn tmp=bgn_new(0);
        vector_pop_back(&tmp.v);
        for(int k=0;k<i;k++)
            vector_push_back(&tmp.v,0);
        int64_t factor=*vector_at(&a.v,i);
        int64_t carry=0;
        for(int j=0;j<vector_size(&b.v);j++)
        {
            int64_t pr=*vector_at(&b.v,j)*factor+carry;
            carry=pr/RADIX;
            vector_push_back(&tmp.v,pr%RADIX);
        }
        if(carry!=0)
            vector_push_back(&tmp.v,carry);
        bgn x=bgn_add(c,tmp);
        bgn_del(c);
        bgn_del(tmp);
        c=x;
    }
    if(a.sign==b.sign)
        c.sign=POSITIVE;
    else
        c.sign=NEGATIVE;
    return c;
}

bgn* bgn_mul(bgn *a,bgn *b)
{

}


char s[100000000];
int main(int argc,char *argv[])
{
    bgn pr=bgn_new(1);
    for(int i=2;i<10000;i++)
    {
        bgn now=bgn_new(i);
        bgn tmp=bgn_mul_nor(now,pr);
        bgn_del(now);
        bgn_del(pr);
        pr=tmp;
    }
    bgn_str(s,pr);
    printf("%s",s);
}
