#include "adt.h"

block *pop(stack *st)
{
	if(st->NULL)
	{return NULL;}
	block *d = malloc(sizeof(block));
	d->tag = st->data->tag;
	d->data = st->data->data;
	stack *t = st;
	st = st->prev;
	free(t);
	return d;
}
block *push(stack *st,block *b)
{
	stack *d = malloc(sizeof(stack));
	d->data = b;
	d->prev = st;
	st->next = d;
	st = st->next;
	return b;
}
block *peek(stack *st)
{
	if(st->NULL)
	{return NULL;}
	return st->data;
}

treenode *insertAsChild(treenode *parent, node *child, Type tag)
{
	if(child==NULL)
	{return NULL;}
	treenode *t = malloc(sizeof(treenode));
	t->data = child;
	t->tag = tag;
	t->right = NULL;
	t->parent = parent;
	if(parent==NULL)
	{root=t;}
	return t;
}
treenode *insertAsNextSibling(treenode *child, node *right, Type tag)
{
	if(child==NULL||right==NULL||child->right!=NULL)
	{return NULL;}
	treenode *t = malloc(sizeof(treenode));
	t->data = right;
	t->tag = tag;
	t->right = NULL;
	t->parent = child->parent;
	child->right = t;
	return t;
	
}
treenode *getRoot(treenode *child)
{
	treenode *t = child;
	if(t==NULL)
	{return NULL;}
	while(t->parent!=NULL)
	{
		t=t->parent;
	}
	return t;
}
void *printTraversal(treenode *root)
{
	treenode *t = root;
	if(t!=NULL)
	{
		if(t->child==NULL)
		{
			if(t->tag!=NONTERMINAL)
			print("%s",t->token->lexeme);
		}
		else
		{
			printTraversal(t->child);
		}
		printTraversal(t->right);
	}
}
