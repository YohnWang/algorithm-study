#include<stdio.h>
#include<stdlib.h>

typedef struct tree tree;
struct tree
{
    tree *parent;
    tree *left;
    tree *right;
};

//the primary operations of binary tree

void tree_init(tree *root)
{
    root->parent=NULL;
    root->left=NULL;
    root->right=NULL;
}

static inline tree* tree_left(tree *p)
{
    return p->left;
}
static inline tree* tree_right(tree *p)
{
    return p->right;
}
static inline tree* tree_parent(tree *p)
{
    return p->parent;
}

tree* tree_root(tree *p)
{
    if(tree_parent(p)!=NULL)
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

tree* tree_most_left(tree *root)
{
    if(tree_left(root)!=NULL)
        return tree_most_left(tree_left(root));
    else
        return root;
}
tree* tree_most_right(tree *root)
{
    if(tree_right(root)!=NULL)
        return tree_most_right(tree_right(root));
    else
        return root;
}

void tree_del(tree *node)
{
    if(tree_left(node)==NULL && tree_right(node)==NULL)//the node without any children
    {
        tree *parent=tree_parent(node);
        if(parent==NULL)//the node is the root
            return;
        if(parent->left==node)//is left or right child
            parent->left=NULL;
        else
            parent->right=NULL;
        tree_init(node);//remove any information about tree in this node
    }
    else if(tree_left(node)==NULL && tree_right(node)!=NULL)//the node have a right tree
    {
        tree *parent=tree_parent(node);
        tree *right=tree_right(node);
        if(parent==NULL)//the node is the root
        {
            right->parent=NULL;
            tree_init(node);
            return;
        }
        if(parent->left==node)
            parent->left=right;
        else
            parent->right=right;
        right->parent=parent;
        tree_init(node);
    }
    else if(tree_left(node)!=NULL && tree_right(node)==NULL)//the node have a left tree
    {
        tree *parent=tree_parent(node);
        tree *left=tree_left(node);
        if(parent==NULL)//the node is the root
        {
            left->parent=NULL;//take the left tree as the root
            tree_init(node);
            return;
        }
        if(parent->left==node)//is left or right child
            parent->left=tree_left(node);
        else
            parent->right=tree_left(node);
        left->parent=parent;
        tree_init(node);
    }
    else //the node with two children
    {
        tree *left=tree_left(node),*right=tree_right(node);
        tree *most_right=tree_most_right(left);//used to replace the node
        tree_del(most_right);//delete the node in the tree
        most_right->left=left;
        most_right->right=right;
        tree *parent=tree_parent(node);
        if(parent==NULL)
            most_right->parent=NULL;
        else
        {
            most_right->parent=parent;
            if(tree_left(parent)==node)
                parent->left=most_right;
            else
                parent->right=most_right;
        }
        tree_init(node);
    }
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

//the operations of binary search tree

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
    int b[]={49,1,3,74,7,5,2,6,18,10};
    for(int i=0;i<sizeof a/sizeof a[0];i++)
    {
        tree_init(&a[i].tree);
        a[i].x=b[i];
    }
    for(int i=1;i<sizeof a/sizeof a[0];i++)
    {
        tree_add(&a[0].tree,number_cmp,&a[i].tree);
    }
    printf("%d\n",((struct number*)tree_most_right(&a[0].tree))->x);
    tree_del(&a[1].tree);
    tree_del(&a[5].tree);
    tree_del(&a[9].tree);
    tree_del(&a[0].tree);
    tree_del(&a[7].tree);
    //for(int i=1;i<sizeof a/sizeof a[0];i++)
    //{
    //    tree_del(&a[i].tree);
    //}
    tree_inorder_visit((&a[8].tree),print,NULL);
    printf("\n%d",((struct number*)tree_root(&a[8].tree))->x);
}
