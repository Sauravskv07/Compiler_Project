#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include "utils.h"
#include "adt.h"
#include <string.h>
#include <stdlib.h>

stack *pop(stack *st)
{
	if(st==NULL)
	{return NULL;}
	
	stack *t = st;
	st = st->prev;
	st->next = NULL;

	free(t);

	return st;
}
stack *push(stack *st,ht_item *b)
{
	stack *d = malloc(sizeof(stack));
	d->data = b;
	d->prev = st;
	st->next = d;
	st = st->next;
	return st;
}
ht_item *peek(stack *st)
{
	if(st==NULL)
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
treenode *insertAsNextRightSibling(treenode *child, node *right, Type tag)
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
void printTraversal(treenode *root)
{
	treenode *t = root;
	if(t!=NULL)
	{
		if(t->child==NULL)
		{
			if(t->tag!=NONTERMINAL)
			printf("%s",t->data->token->lexeme);
		}
		else
		{
			printTraversal(t->child);
			printf("%s",t->data->nonterm->key);
			printTraversal(t->child->right);
		}
	}
}
