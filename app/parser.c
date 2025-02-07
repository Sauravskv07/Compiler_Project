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
#include "parseTable.h"
#include "adt.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>


error_list* parseTree(){

	root=NULL;

	errors=NULL;

	stack *st=(stack*)malloc(sizeof(stack));

	ht_item* rhs_rev[MAX_RHS];

	ht_item* bottom=NULL;

	st->data=bottom;
	st->next=NULL;
	st->prev=NULL;

	ht_item* start=ht_search(mapping_table,"program");

	ht_item* end_marker=(ht_item *)malloc(sizeof(ht_item));

	end_marker->index=-2;

	end_marker->key=NULL;

	st=push(st,start);

	ht_item *top;

	Token* nextToken=getNextToken();

	node* temp=(node *)malloc(sizeof(node));
	
	treenode* currentNode = NULL;
	
	int isFirst=1;

	while(peek(st)!=NULL)
	{
		top=peek(st);

		printf("Popped Element = %s\n",top->key);

		st=pop(st);

		if(top->index==ht_search(mapping_table,"e")->index)
		{
			continue;
		}
		
		if(top->index==-2)
		{
			currentNode=currentNode->parent;
			continue;
		}
		
		if(nextToken==NULL)
		{
			printf("REACHED END OF PROGRAM WITHOUT COMPLETE PARSE TREE GENERATION\n");

			error_list* new_error=(error_list*)malloc(sizeof(error_list));
			
			new_error->tk=nextToken;

			new_error->next=errors;
	
			errors=new_error;

			return errors;

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

			printf("Rule used = %d \n",rule_index);
			rule_rhs* rule = rules[rule_index].key;

			while(rule)
			{
				rhs_rev[i]=rule->node;
				i++;	
				rule=rule->next;
			}
			
			printf("NUmber of rules of RHS = %d\n",i);
			for(int j=i-1;j>=0;j--)
			{
				st=push(st,rhs_rev[j]);
			}

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
	
	if((nextToken->index)!=(ht_search(mapping_table,"$")->index))
	{
			printf("Extra Tokens Found \n");
			error_list* new_error=(error_list*)malloc(sizeof(error_list));
			new_error->tk=nextToken;
			new_error->next=errors;
			errors=new_error;
	}

	printf("Done Parsing\n");

	return errors;
}

