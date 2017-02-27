#include<stdio.h>
#include<stdlib.h>

typedef struct tree tree;
struct tree
{
    tree *parent;
    tree *left;
    tree *right;
};

void tree_init(tree *root)
{
    root->parent=root;
    root->left=NULL;
    root->right=NULL;
}

inline tree* tree_left(tree *p)
{
    return p->left;
}
inline tree* tree_right(tree *p)
{
    return p->right;
}
inline tree* tree_parent(tree *p)
{
    return p->parent;
}

tree* tree_root(tree *p)
{
    if(tree_parent(p)!=p)
        return tree_root(tree_parent(p));
    else
        return p;
}

void tree_insert(tree *root,tree *left,tree *right)
{
    root->left=left;
    root->right=right;
    if(left!=NULL)
        left->parent=root;
    if(right!=NULL)
        right->parent=root;
}

void tree_prev_visit(tree *root,void (*handler)(tree *root,void *args),void *args)
{
    //recursive
    if(root!=NULL)
    {
        handler(root,args);
        tree_prev_visit(root->left,handler,args);
        tree_prev_visit(root->right,handler,args);
    }

}

void tree_inorder_visit(tree *root,void (*handler)(tree *root,void *args),void *args)
{
    //recursive
    if(root!=NULL)
    {
        tree_inorder_visit(root->left,handler,args);
        handler(root,args);
        tree_inorder_visit(root->right,handler,args);
    }
}

void tree_post_visit(tree *root,void (*handler)(tree *root,void *args),void *args)
{
    //recursive
    if(root!=NULL)
    {
        tree_post_visit(root->left,handler,args);
        tree_post_visit(root->right,handler,args);
        handler(root,args);
    }

}



void tree_add(tree *root,int (*cmp)(tree *a,tree*b),tree *new)
{
    if(cmp(new,root))
    {
        if(tree_left(root)!=NULL)
            tree_add(tree_left(root),cmp,new);
        else
            tree_insert(root,new,tree_right(root));
    }
    else
    {
        if(tree_right(root)!=NULL)
            tree_add(tree_right(root),cmp,new);
        else
            tree_insert(root,tree_left(root),new);
    }
}

void tree_del(tree *node)
{
    if(tree_left(node)==NULL && tree_right(node)==NULL)
    {
        tree *parent=node->parent;
        if(parent->left==node)
            parent->left=NULL;
        else
            parent->right=NULL;
    }
    else if(tree_left(node)==NULL && tree_right(node)!=NULL)
    {
        tree *parent=node->parent;
        if(parent->left==node)
            parent->left=tree_right(node);
        else
            parent->right=tree_right(node);
    }
    else if(tree_left(node)!=NULL && tree_right(node)==NULL)
    {
        tree *parent=node->parent;
        if(parent->left==node)
            parent->left=tree_left(node);
        else
            parent->right=tree_left(node);
    }
    else
    {
        tree *left=tree_left(node);
        while(tree_right(left))
        {
            left=tree_right(left);
        }
        tree_del(left);

        left->left=node->left;
        left->right=node->right;
        if(tree_parent(node)!=node)
            left->parent=node->parent;
        else
            left->parent=left;
    }

}

struct number
{
    tree tree;
    int x;
};

void print(tree *p,void *args)
{
    struct number *r=(struct number*)p;
    printf("%d ",r->x);
}

int number_cmp(tree *a,tree *b)
{
    struct number *x=(void*)a,*y=(void*)b;
    return x->x<y->x;
}

int main(int argc,char *argv[])
{
    struct number a[10];
    int b[]={9,1,3,4,7,5,2,6,8,10};
    for(int i=0;i<sizeof a/sizeof a[0];i++)
    {
        tree_init(&a[i].tree);
        a[i].x=b[i];
    }
    for(int i=1;i<sizeof a/sizeof a[0];i++)
    {
        tree_add(&a[0].tree,number_cmp,&a[i].tree);
    }
    tree_del(&a[0].tree);
    tree_inorder_visit(tree_root(&a[8].tree),print,NULL);
    printf("\n%d",((struct number*)tree_root(&a[8].tree))->x);
}
