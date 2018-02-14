#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdint.h>
#include<time.h>

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
    //static int count=0;
    //printf("call %d\n",++count);
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
        if(new_size<=cap)
            v->size=new_size;
        else
        {
            vector_recapacity(v,new_size);
            v->size=new_size;
        }
    }
}

static inline void vector_fit(vector *v)
{
    vector_recapacity(v,vector_size(v));
}

//vector interface

static vector* vector_init(vector *v)
{
    v->size=0;
    v->capacity=0;
    v->a=NULL;
    return v;
}

static void vector_del(vector *v)
{
    v->size=0;
    v->capacity=0;
    free(v->a);
    v->a=NULL;
}

static inline void vector_clear(vector *v)
{
    v->size=0;
}

//using
static inline void vector_push_back(vector *v,Etype e)
{
    int size=vector_size(v);
    int cap =vector_capacity(v);
    if(size==cap)
        vector_recapacity(v,cap+cap/2+1);
    v->a[v->size++]=e;
}

static inline void vector_pop_back(vector *v)
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
    return vector_at(v,vector_size(v)-1);
}

static inline Etype* vector_front(vector *v)
{
    return vector_at(v,0);
}

static inline Etype* vector_begin(vector *v)
{
    return &v->a[0];
}

static inline Etype* vector_end(vector *v)
{
    return &v->a[vector_size(v)];
}

static inline Etype* vector_data(vector *v)
{
    return vector_begin(v);
}

static void vector_assign(vector *new,vector *v)
{
    vector_del(new);
    vector_resize(new,vector_size(v));
    memcpy(vector_data(new),vector_data(v),vector_size(new)*sizeof(Etype));
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
    int len=0;
    if(b.sign==NEGATIVE)
        len=sprintf(tmp,"-%d",*vector_back(&b.v));
    else
        len=sprintf(tmp,"%d",*vector_back(&b.v));
    strcpy(s,tmp);
    int cnt=0;
    for(int i=vector_size(&b.v)-2;i>=0;i--)
    {
        sprintf(tmp,"%.9d",*vector_at(&b.v,i));
        strcpy(s+len+cnt*9,tmp);
        cnt++;
    }
    return s;
}

void bgn_neg(bgn *b)
{
    if(b->sign==POSITIVE)
        b->sign=NEGATIVE;
    else
        b->sign=POSITIVE;
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

bgn bgn_cpy(bgn a)
{
    bgn c;
    vector_init(&c.v);
    vector_assign(&c.v,&a.v);
    c.sign=a.sign;
    return c;
}

static bgn bgn_add_mov_nosign(bgn a, bgn b) //a+=b ,and must be a=bgn_add_mov_nosign(a,b);
{
    int i;
    int32_t carry=0;
    for(i=0;i<vector_size(&a.v)&&i<vector_size(&b.v);i++)
    {
        int32_t sum=*vector_at(&a.v,i)+*vector_at(&b.v,i)+carry;
        carry=sum/RADIX;
        *vector_at(&a.v,i)=sum%RADIX;
    }
    while(i<vector_size(&a.v))
    {
        int32_t sum=*vector_at(&a.v,i)+carry;
        carry=sum/RADIX;
        *vector_at(&a.v,i)=sum%RADIX;
        i++;
    }
    while(i<vector_size(&b.v))
    {
        int32_t sum=*vector_at(&b.v,i)+carry;
        carry=sum/RADIX;
        vector_push_back(&a.v,sum%RADIX);
        i++;
    }
    if(carry!=0)
        vector_push_back(&a.v,carry);
    return a;
}

static bgn bgn_sub_mov_nosign_bg(bgn a,bgn b)
{
    int i;
    int32_t carry=0;
    for(i=0;i<vector_size(&b.v);i++)
    {
        int32_t diff=*vector_at(&a.v,i)-*vector_at(&b.v,i)-carry;
        if(diff<0)
        {
            diff+=RADIX;
            carry=1;
        }
        else
            carry=0;
        *vector_at(&a.v,i)=diff;
    }
    while(i<vector_size(&a.v))
    {
        int32_t diff=*vector_at(&a.v,i)-carry;
        if(diff<0)
        {
            diff+=RADIX;
            carry=1;
        }
        else
            carry=0;
        *vector_at(&a.v,i)=diff;
        i++;
    }
    while(*vector_back(&a.v)==0)
        vector_pop_back(&a.v);
    return a;
}

static bgn bgn_sub_mov_nosign_lw(bgn a, bgn b)
{
    int i;
    int32_t carry=0;
    for(i=0;i<vector_size(&a.v);i++)
    {
        int32_t diff=*vector_at(&b.v,i)-*vector_at(&a.v,i)-carry;
        if(diff<0)
        {
            diff+=RADIX;
            carry=1;
        }
        else
            carry=0;
        *vector_at(&a.v,i)=diff;
    }
    while(i<vector_size(&b.v))
    {
        int32_t diff=*vector_at(&b.v,i)-carry;
        if(diff<0)
        {
            diff+=RADIX;
            carry=1;
        }
        else
            carry=0;
        vector_push_back(&a.v,diff);
        i++;
    }
    while(*vector_back(&a.v)==0)
        vector_pop_back(&a.v);
    return a;
}

bgn bgn_sub_mov_nosign(bgn a,bgn b)
{
    int cmp=bgn_cmp_nosign(a,b);
    if(cmp>0)
    {
        a=bgn_sub_mov_nosign_bg(a,b);
        a.sign=POSITIVE;
    }
    else if(cmp<0)
    {
        a=bgn_sub_mov_nosign_lw(a,b);
        a.sign=NEGATIVE;
    }
    else
    {
        vector_clear(&a.v);
        vector_push_back(&a.v,0);
        a.sign=POSITIVE;
    }
    return a;
}

bgn bgn_sub_mov(bgn a,bgn b);
bgn bgn_add_mov(bgn a,bgn b)
{
    if(a.sign==b.sign)
        a=bgn_add_mov_nosign(a,b);
    else if(a.sign==POSITIVE)
    {
        bgn_neg(&b);
        a=bgn_sub_mov(a,b);
        bgn_neg(&b);
    }
    else
    {
        a.sign=POSITIVE;
        a=bgn_sub_mov(a,b);
        bgn_neg(&a);
    }
    return a;
}

bgn bgn_sub_mov(bgn a,bgn b)
{
    if(a.sign==POSITIVE&&b.sign==POSITIVE)
        a=bgn_sub_mov_nosign(a,b);
    else if(a.sign==NEGATIVE&&b.sign==NEGATIVE)
    {
        a=bgn_sub_mov_nosign(a,b);
        bgn_neg(&a);
    }
    else if(a.sign==POSITIVE&&b.sign==NEGATIVE)
    {
        bgn_neg(&b);
        a=bgn_add_mov(a,b);
        bgn_neg(&b);
    }
    else
    {
        bgn_neg(&a);
        a=bgn_add_mov(a,b);
        a.sign=NEGATIVE;
    }
    return a;
}

bgn bgn_add(bgn a,bgn b)
{
    bgn c=bgn_cpy(a);
    c=bgn_add_mov(c,b);
    return c;
}

bgn bgn_sub(bgn a,bgn b)
{
    bgn c=bgn_cpy(a);
    c=bgn_sub_mov(c,b);
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

static bgn bgn_mul_nor(bgn a,bgn b)  // size of a should be bigger than size of b
{
    bgn c=bgn_new(0);
    bgn tmp;
    vector_init(&tmp.v);
    vector_recapacity(&tmp.v,vector_size(&a.v)+vector_size(&b.v)+1);
    vector_recapacity(&c.v,vector_size(&a.v)+vector_size(&b.v)+1);
    for(int i=0;i<vector_size(&a.v);i++)
    {
        vector_clear(&tmp.v);
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
        c=bgn_add_mov_nosign(c,tmp);
    }
    bgn_del(tmp);
    if(a.sign==b.sign)
        c.sign=POSITIVE;
    else
        c.sign=NEGATIVE;
    return c;
}

bgn bgn_mul(bgn a,bgn b)
{
    if(vector_size(&a.v)>vector_size(&b.v))
        return bgn_mul_nor(b,a);
    else
        return bgn_mul_nor(a,b);
}
char s[1000000];
int main(int argc,char *argv[])
{
    clock_t start=clock();
    bgn pr=bgn_new(1);
    for(int i=2;(i<=100000);i++)
    {
        bgn now=bgn_new(i);
        bgn tmp=bgn_mul(pr,now);
        bgn_del(now);
        bgn_del(pr);
        pr=tmp;
    }
    bgn_str(s,pr);
    printf("%s",s);
    printf("\ntime=%ld\n",clock()-start);
}
