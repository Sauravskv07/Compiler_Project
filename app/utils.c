#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include "utils.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

ht_items_list * bin_to_list(unsigned long n)
{
	ht_items_list * st = malloc(sizeof(ht_items_list));
	st->next=NULL;
	ht_items_list *t=st;
	ht_items_list *x=NULL;

	for(int i=0;i<64;i++)
	{
		if(n&(unsigned long)pow(2,i))
		{
			x=(ht_items_list*)malloc(sizeof(ht_items_list));
			x->node=tokensList[i];
			//printf("x->node->key = %s\n",x->node->key);
			x->next=NULL;
			t->next=x;
			t=x;
		}	
	}

	return st;
}
unsigned long unionLists(unsigned long items,unsigned long temp)
{
	items = items|temp;
	return items;
}
unsigned long first(ht_item *term)
{
	if(term->tag==1)
	{
		return pow(2, term->index);
	}
	unsigned long items = 0;
	int i=0;
	while(i<rule_count && term!=rules[i].lhs)
	{i++;}
	unsigned long temp;
	
	while(i<rule_count && term==rules[i].lhs)
	{	
		temp = first(rules[i].key->node);

		unsigned long temp2=temp;

		rule_rhs *lt=rules[i].key->next;

		while((temp2/2)%2==1 && lt!=NULL)
		{
			temp2 = first(lt->node);
			
			temp = unionLists(temp,temp2);

			lt=lt->next;
		}

		if((temp2/2)%2!=1)
		{
			temp = temp & (~2);
		}

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


unsigned long firstofRule(rule_rhs* rhs)
{
	if(rhs==NULL)
		return 2;

	unsigned long items=first(rhs->node);
	
	if((items/2)%2==1)
	{
		items &= (~2);
	
		items=unionLists(items,firstofRule(rhs->next));					
	}
	
	return items;
}

ht_items_list * computeFirstofRule(rule_rhs* rhs)
{
	ht_items_list * x = bin_to_list(firstofRule(rhs));

	return x;
}

unsigned long follow(ht_item *term)
{
	if(term->tag==1)
	{return pow(2, term->index);}
	unsigned long items = 0;
	int i=0;
	rule_rhs *t=NULL;
	unsigned long temp;
	while(i<rule_count && rules[i].lhs!=NULL)
	{
		t = rules[i].key;
		while(t!=NULL)
		{
			if(t->node==term)
			{break;}
			t = t->next;
		}
		if(t==NULL)
		{
			i++;
			continue;
		}


		if(t->node==term && t->next==NULL)
		{temp = follow(rules[i].lhs);}
		if(t->node==term && t->next!=NULL)
		{temp = first(t->next->node);}

		unsigned long temp2=temp;
		rule_rhs *lt=rules[i].key->next;
		while(temp2%2==1 && lt!=NULL)
		{
			if(lt!=NULL)
			{
				temp2 = first(lt->node);
				temp = unionLists(temp,temp2);
				lt=lt->next;
			}
		}
		if(temp2%2==1)
		{
			temp = temp | (1);
		}
		temp = temp & (~2);

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
	lt=lt->next;
	while(lt!=NULL)
	{
		printf("%s ,",lt->node->key);
		lt = lt->next;
	}

}
