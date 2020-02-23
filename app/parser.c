#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include "utils.h"
#include "parseTable.h"
#include "adt.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>


error_list* parseTree(){

	root=NULL;

	errors=NULL;

	stack *st=NULL;

	ht_item* rhs_rev[MAX_RHS];

	ht_item* bottom=NULL;

	ht_item* start=ht_search(mapping_table,"program");

	ht_item* end_marker=(ht_item *)malloc(sizeof(ht_item));

	end_marker->index=-1;

	end_marker->key=NULL;

	st=push(st,bottom);

	st=push(st,start);

	ht_item *top;

	Token* nextToken=getNextToken();

	node* temp=(node *)malloc(sizeof(node));
	
	treenode* currentNode = NULL;

	top=peek(st);
	
	int isFirst=1;

	printf("HOLA \n");
	while(top!=NULL)
	{
		if(nextToken==NULL)
		{
			printf("REACHED END OF PROGRAM WITHOUT COMPLETE PARSE TREE GENERATION\n");

			error_list* new_error=(error_list*)malloc(sizeof(error_list));
			
			new_error->tk=nextToken;

			new_error->next=errors;
	
			errors=new_error;

			return errors;

		}

		st=pop(st);

		printf("HOLA1 \n");

		if(top->index==-1)
		{
			currentNode=currentNode->parent;
		}	
		

		if(top->index==ht_search(mapping_table,"e")->index)
		{
			continue;
		}

		printf("HOLA2 \n");
	
		if(top->tag==2)
		{
			temp->nonterm = top;

			if(isFirst)
			{
				currentNode=insertAsChild(currentNode, temp,top->tag );
				isFirst=0;
			}
			else
			{
				currentNode=insertAsNextRightSibling(currentNode, temp,top->tag);
			}

			st=push(st,end_marker);

			int i=0;
			
			int rule_index=parse_table[top->index][nextToken->index];

			if(rule_index==-1)
			{
				error_list* new_error=(error_list*)malloc(sizeof(error_list));
				new_error->tk=nextToken;
				new_error->next=errors;
				errors=new_error;

				nextToken=getNextToken();

				while(nextToken!=NULL)
				{
					rule_index=parse_table[top->index][nextToken->index];
					if(rule_index!=-1)
					{
						break;
					}
				}
				
				if(rule_index==-1)
					continue;
			}

			rule_rhs* rule = rules[rule_index].key;

			while(rule)
			{
				rhs_rev[i]=rule->node;
				i++;	
				rule=rule->next;
			}
			
			for(int j=i-1;j>=1;j--)
			{
				st=push(st,rhs_rev[j]);
			}
			st=push(st,rhs_rev[0]);

			isFirst=1;

		}
	
		else if(top->tag==1)
		{
			if(top->index==nextToken->index)
			{
				nextToken=getNextToken();
			}
			else
			{
				error_list* new_error=(error_list*)malloc(sizeof(error_list));
				new_error->tk=nextToken;
				new_error->next=errors;
				errors=new_error;

				nextToken=getNextToken();

				while(nextToken!=NULL)
				{
					if(top->index==nextToken->index)
					{
						break;
					}
				}
			
				if(nextToken==NULL)
					continue;
			}
			
			temp->token=nextToken;

			if(isFirst==1)
			{
				currentNode=insertAsChild(currentNode, temp, 1);
				isFirst=0;
			}
			else
			{
				currentNode=insertAsNextRightSibling(currentNode, temp, 1);
			}
		}
	}
	
	if(nextToken!=NULL)
	{
			printf("Extra Tokens Found \n");
			error_list* new_error=(error_list*)malloc(sizeof(error_list));
			new_error->tk=nextToken;
			new_error->next=errors;
			errors=new_error;
	}
	return errors;
}

