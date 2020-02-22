#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include "utils.h"
#include "parseTable.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

void create_parse_table()
{
	int index_e = ht_search(mapping_table,"e")->index;

	for(int i=0;i<rule_count;i++)
	{
		ht_item* nonterminal=rules[i].lhs;
		
		ht_items_list * first=computeFirstofRule(rules[i].key)->next;

		int contains_e=0;
		int contains_dollar=0;

		while(first!=NULL)
		{
			if(first->node->index==index_e)
				contains_e=1;

			parse_table[nonterminal->index][first->node->index]=rules[i].key;
			
			first=first->next;

		}
		
		if(contains_e==1)
		{
			ht_items_list * follow=computeFollow(nonterminal)->next;

			while(follow!=NULL)
			{
				parse_table[nonterminal->index][follow->node->index]=rules[i].key;
	
				follow=follow->next;
			}		
		}
	}

}
