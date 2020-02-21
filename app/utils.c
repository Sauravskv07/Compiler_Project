#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include "utils.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

ht_items_list * bin_to_list(ht_item* tokensList[],int n)
{
	int i=0;
	ht_items_list * st = malloc(sizeof(ht_items_list));
	st->node = tokensList[0];
	ht_items_list *t=st;
	ht_items_list *x=NULL;
	while(tokensList[i]!=NULL && n&pow(2,i)!=0)
	{
		x = malloc(sizeof(ht_items_list));
		x->node = tokensList[i];
		t->next=x;
		t=x;
	}
	return st;
}
int unionLists(int items,int temp)
{
	items = items&temp;
	return items;
}
int first(ht_item *term)
{
	if(term->tag==1)
	{return pow(2, term->index);}
	int items = 0;
	int i=0;
	while(i<MAX_RULES && term!=rules[i].lhs)
	{i++;}
	int temp;
	while(i<MAX_RULES && term==rules[i].lhs)
	{
		temp = first(rules[i].key->node);
		items = unionLists(items,temp);
		i++;
	}
	
	return items;
}
ht_items_list * computeFirst(ht_item *term,ht_item* tokensList[])
{
	ht_items_list * x = bin_to_list(tokensList,first(term));
	return x;
}

int follow(ht_item *term)
{
	if(term->tag==1)
	{return pow(2, term->index);}
	int items = 0;
	int i=0;
	rule_rhs *t=NULL;
	int temp;
	while(i<MAX_RULES && rules[i].lhs!=NULL)
	{
		t = rules[i].key;
		while(t!=NULL)
		{
			if(t->node==term)
			t = t->next;
		}
		if(t->node==term && t->next==NULL)
		{temp = follow(rules[i].lhs);}
		if(t->node==term && t->next!=NULL)
		{temp = first(t->next->node);}
		items = unionLists(items,temp);
		i++;
	}
	return items;
}
ht_items_list * computeFollow(ht_item *term,ht_item* tokensList[])
{
	ht_items_list * x = bin_to_list(tokensList,follow(term));
	return x;
}

void printmyList(ht_items_list * lt)
{
	while(lt!=NULL)
	{
		printf("%s",lt->node->key);
		lt = lt->next;
	}
}