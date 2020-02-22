rule_rhs*** create_parse_table()
{
	for(int i=0;i<num_nonterminals;i++)
	{
		ht_item* nonterminal=tokensList[i+num_terminals];

		for(int j=0;j<num_terminal;j++)
		{
			parse_table[i][j]=NULL;
		}
	
		ht_items_list * first=computeFirst(nonterminal)->next;

		while(first!=NULL)
		{
			parse_table[i][first->node->index]=;
			first=first->next;
		}
		
		ht_items_list * follow=computeFollow(nonterminal)->next;
		
		while(follow!=NULL)
		{
			parse_table[i][follow->node->index]=;
			follow=follow->next;
		}
	}

	return parse_table;
}
