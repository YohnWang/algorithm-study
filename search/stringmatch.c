#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int bf(char s[],char t[])
{
    int i=0,j=0;
    while(s[i]!='\0'&&t[j]!='\0')
    {
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(t[j]=='\0')
        return i-j;
    else
        return -1;
}


void deduce_next(char t[],int next[],int len)
{
    int i=0,j=-1;
    next[0]=-1;
    //dynamic programming
    while(t[i]!='\0')
    {
        if(j==-1||t[i]==t[j]) //t[i]==t[next[i-1]+1] then next[i]=next[i-1]+1
        {
            i++;
            j++;
            next[i]=j;
        }
        else
            j=next[j];
    }
}

int kmp(char s[],char t[])
{
    int len=strlen(t);
    int next[len]; //only can be compiled whit c99 supported
    deduce_next(t,next,len);
    //the same as bf ,only change the 'j==-1' and 'j=next[j]'
    //the kmp process,like the finite automaton
    int i=0,j=0;
    while(s[i]!='\0'&&j<len) //don't use t[j]=='\0' because j=-1
    {
        if(j==-1||s[i]==t[j]) //change here
        {
            i++;
            j++;
        }
        else
        {
            j=next[j]; //change here
        }
    }
    if(j==len) //don't use t[j]=='\0' because j=-1
        return i-j;
    else
        return -1;
}

int main(int argc,char *argv[])
{
    char *s="abaabaabeca";
    char *t="abaabe";
    printf("%d\n",kmp(s,t));
}
