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

int main(int argc,char *argv[])
{
    struct number a[10];
    for(int i=0;i<sizeof a/sizeof a[0];i++)
    {
        tree_init(&a[i].tree);
        a[i].x=i;
    }
    tree_insert(&a[0].tree,&a[1].tree,&a[2].tree);
    tree_insert(&a[1].tree,&a[4].tree,&a[3].tree);
    tree_insert(&a[2].tree,NULL,&a[5].tree);
    tree_insert(&a[5].tree,&a[6].tree,&a[7].tree);
    tree_insert(&a[7].tree,&a[8].tree,NULL);
    tree_prev_visit(&a[0].tree,print,NULL);
    printf("\n");
    tree_inorder_visit(&a[0].tree,print,NULL);
    printf("\n");
    tree_post_visit(&a[0].tree,print,NULL);
    printf("\n");
}
