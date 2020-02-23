#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include "utils.h"
#include "adt.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>

parse_tree=NULL;
parse_stack=NULL;

struct error_list* parse(treenode* tn, stack* st){

	ht_item** rhs_rev=(ht_item *)malloc(sizeof(ht_item)*MAX_RHS);

	ht_item* bottom=ht_search(mapping_table,"$");

	ht_item* start=ht_search(mapping_table,"program");

	ht_item* end_marker=(ht_item *)malloc(sizeof(ht_item));

	end_marker->index=-1;

	end_marker->key=NULL;

	st=push(st,bottom,0);

	st=push(st,start,1);

	stack *top;

	Token* nextToken=getNextToken();

	parse_tree=(treenode*)malloc(sizeof(treenode));
	
	parse_tree->data=ht_search(mapping_table,"program");
	parse_tree->child=NULL;
	parse_tree->right=NULL
	parse_tree->parent=NULL;

	treenode* currentNode=parse_tree;
	
	while((peek(st)->data->index)!=bottom->index)
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
		top=peek(st);

		st=pop(st);

		if(top->data->index==-1)
		{
			currentNode=currentNode->parent;
		}	
		

		if(top->data->index==ht_search(mapping_table,"e")->index)
		{
			continue;
		}

		else if(top->data->tag==2)
		{

			node* temp=(node*)malloc(sizeof(node))

			temp->nonterm = top->data;

			if(top->status==1)
			{
				currentNode=insertAsChild(currentNode, temp,top->data->tag );
			}
			else
			{
				currentNode=insertAsNextSibling(currentNode, temp,top->data->tag);
			}

			st=push(st,end_marker,0);

			int i=0;
			
			int rule_index=parse_table[top->data->index][nextToken->index];

			if(rule==-1)
			{
				error_list* new_error=(error_list*)malloc(sizeof(error_list));
				new_error->tk=nextToken;
				new_error->next=errors;
				errors=new_error;

				nextToken=getNextToken();

				while(nextToken!=NULL)
				{
					rule_index=parse_table[top->data->index][nextToken->index];
					if(rule_index!=-1)
					{
						break;
					}
				}
			}

			rule_rhs* rule = rules[rule_index]->key;

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
			st=push(st,rhs_rev[0],1);

		}
	
		else if(top->data->tag==1)
		{
			if(top->data->index==nextToken->index)
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
					if(top->data->index==nextToken->index)
					{
						break;
					}
				}
			}

			node* temp=(node*)malloc(sizeof(node));
			
			temp->token=nextToken;

			if(top->status==1)
			{
				currentNode=insertAsChild(currentNode, temp, 1);
			}
			else
			{
				currentNode=insertAsNextSibling(currentNode, temp, 1);
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

