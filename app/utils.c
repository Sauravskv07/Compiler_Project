#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include "utils.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

ht_items_list * bin_to_list(int x)
{
	return NULL;
}
int unionLists(int items,int temp)
{
	pow(2, 4);				// Change format.
	return 0;
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
ht_items_list * computeFirst(ht_item *term)
{
	ht_items_list * x = bin_to_list(first(term));
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
ht_items_list * computeFollow(ht_item *term)
{
	ht_items_list * x = bin_to_list(follow(term));
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