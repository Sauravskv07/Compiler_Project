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

	ht_item* bottom=ht_search(mapping_table,"$");

	st->data=bottom;
	st->next=NULL;
	st->prev=NULL;

	ht_item* start=ht_search(mapping_table,"program");
	st = push(st,start);

	ht_item* end_marker=(ht_item *)malloc(sizeof(ht_item));

	end_marker->index=-2;

	end_marker->key=NULL;

	ht_item *top;

	Token* nextToken;

	node* temp=(node *)malloc(sizeof(node));
	temp->nonterm = start;
	
	treenode* currentNode = root;
	treenode* tempNode = NULL;
	root = insertAsChild(NULL,temp,2);
	

	while(peek(st)!=NULL && peek(st)!=bottom)
	{
		printf("%s",peek(st)->key);
		top=peek(st);
		if(top==end_marker){st=pop(st);currentNode=currentNode->parent;continue;}
		printf("Popped Element = %s\n",top->key);	
		if(top->index==ht_search(mapping_table,"e")->index)
		{
			st=pop(st);continue;
		}

		
		while(1)
		{
			nextToken=getNextToken();
			if(nextToken==NULL){break;}
			if(top->tag==1 && top->index == nextToken->index)
			{
				st=pop(st);
				currentNode->data->token = nextToken;
				currentNode->tag = 1;
				currentNode = currentNode->right;
				break;
			}
			if(top->tag==2 && parse_table[top->index][nextToken->index]!=-1)
			{
				st=pop(st);
				rule_rhs* rule = rules[parse_table[top->index][nextToken->index]].key;
				int i=1;
				rhs_rev[0]=rule->node;
				temp=(node *)malloc(sizeof(node));
				temp->nonterm = rhs_rev[0];
				currentNode = insertAsChild(currentNode,temp,2);
				tempNode = currentNode;
				rule=rule->next;
				while(rule)
					{
						rhs_rev[i]=rule->node;
						temp=(node *)malloc(sizeof(node));
						temp->nonterm = rhs_rev[i];
						tempNode = insertAsNextRightSibling(tempNode,temp,2);
						i++;	
						rule=rule->next;
					}
			
					printf("Number of rules of RHS = %d\n",i);
					for(int j=i-1;j>=0;j--)
					{
						st=push(st,rhs_rev[j]);
					}
					st=push(st,end_marker);
					break;
			}
		}
		if(nextToken==NULL && peek(st)!=bottom)
		{
			printf("REACHED END OF PROGRAM WITHOUT COMPLETE PARSE TREE GENERATION\n");
			printf("%s",peek(st)->key);
			error_list* new_error=(error_list*)malloc(sizeof(error_list));
			new_error->tk=nextToken;
			new_error->next=errors;
			errors=new_error;
			return errors;
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

