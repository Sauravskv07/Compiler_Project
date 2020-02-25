/*
GROUP NO. = 46
2017A7PS0006P PIKLU PAUL
2017A7PS0007P RAJABABU SAIKIA
2017A7PS0090P SAURAV VIRMANI
2017A7PS0111P SIDDHANT KHARBANDA
2017A7PS0275P SREYAS RAVICHANDRAN
*/
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
	if(st!=NULL)
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
	t->child = NULL;
	t->parent = parent;
	if(parent==NULL)
	{root=t;}
	else
	parent->child = t;
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
	t->child = NULL;
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
			else
			printf("%s",t->data->nonterm->key);
		}
		else
		{
			printTraversal(t->child);
			printf("%s",t->data->nonterm->key);
			//printf("-");
			t=t->child;
			while(t!=NULL)			
			{printTraversal(t->right);t=t->right;}
		}
	}
}

void printTraversal2(treenode *root)
{
	treenode *t = root;
	if(t!=NULL)
	{
		if(t->child==NULL)
		{
			if(t->tag!=NONTERMINAL)
			printf("%s",t->data->token->lexeme);
			else
			printf("%s",t->data->nonterm->key);
		}
		else
		{
			printf("%s",t->data->nonterm->key);
			printTraversal2(t->child);
			while(t!=NULL)			
			{printTraversal2(t->right);t=t->right;}
		}
	}
}
