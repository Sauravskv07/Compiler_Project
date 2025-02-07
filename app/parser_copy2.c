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

void validateLexError(Token* nextToken)
{
		while(nextToken!=NULL && nextToken->index==-1)
		{
				printf("INVALID TOKEN. LEXICAL ERROR.\n");
				printf("%s %d",nextToken->lexeme,nextToken->LN);
				error_list* new_error=(error_list*)malloc(sizeof(error_list));
				new_error->tk=nextToken;
				new_error->next=errors;
				errors=new_error;
				nextToken=getNextToken();
		}
}
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

	Token* nextToken=NULL;

	node* temp=(node *)malloc(sizeof(node));
	temp->nonterm = start;
	
	root = insertAsChild(NULL,temp,2);
	treenode* currentNode = root;
	treenode* tempNode = NULL;
	
	nextToken=getNextToken();
	validateLexError(nextToken);
	//while(nextToken!=NULL)
	//{printf("Extra Tokens Found %d \n",nextToken->index);nextToken=getNextToken();}

	while(peek(st)!=NULL && peek(st)!=bottom)
	{
		//printf("ugiubkjnkj %s\n",peek(st)->key);
		printf("test at %s\n", currentNode->data->nonterm->key);
			printf("test at %s\n", peek(st)->key);
			printf("test at %sppp\n", nextToken->lexeme);
		top=peek(st);
		if(top==end_marker){
			while(peek(st)==end_marker)
			{
				//printf("kihdkashdnkhnk %s\n",peek(st)->key);
				st=pop(st);
				tempNode = currentNode;
				if(currentNode!=NULL)
				currentNode=currentNode->parent;
				//else printf("aaaaa\n");
			}
			if(tempNode!=NULL && tempNode->right!=NULL)
			currentNode = tempNode->right;
			//printf("ugiubkjnkj2 %s\n",peek(st)->key);
			continue;}
		//printf("Popped Element = %s\n",top->key);	
		//printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa %d",top);
		if(top!=NULL && top->index==ht_search(mapping_table,"e")->index)
		{
			if(currentNode==NULL)
			printf("jdgujuasd");
			//printf("test at %s", currentNode->data->nonterm->key);
			//currentNode = currentNode->parent;//st=pop(st);
			while(currentNode!=NULL && currentNode->right==NULL){currentNode = currentNode->parent;st=pop(st);}
			//if(currentNode!=NULL){currentNode = currentNode->right;st=pop(st);}
			//printf("test at %s", currentNode->data->nonterm->key);
			//printf("test at %s", peek(st)->key);
			//printf("test at %sppp", nextToken->lexeme);
			continue;
		}

		
		while(1)
		{
			if(nextToken==NULL){break;}
			if(top->tag==1 && top->index == nextToken->index)
			{
				//printf("jhsvdbdjasbdjkb %d \n",nextToken->index);
				st=pop(st);
				temp=(node *)malloc(sizeof(node));
				temp->token = nextToken;
				currentNode = insertAsChild(currentNode,temp,1);
				//if(currentNode->right!=NULL)currentNode = currentNode->right;
				//else st=pop(st);
				currentNode = currentNode->parent;
				while(currentNode!=NULL && currentNode->right==NULL){currentNode = currentNode->parent;st=pop(st);}
				currentNode = currentNode->right;
			//if(currentNode!=NULL){currentNode = currentNode->right;st=pop(st);}
				//else st=pop(st);
				nextToken=getNextToken();
				validateLexError(nextToken);
				break;
			}
			else if(top->tag==2 && parse_table[top->index][nextToken->index]!=-1)
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
			
					//printf("Number of rules of RHS = %d\n",i);
					st=push(st,end_marker);
					for(int j=i-1;j>=0;j--)
					{
						st=push(st,rhs_rev[j]);
					}
					break;
			}
			else if(top->tag==2 && parse_table[top->index][ht_search(mapping_table,"e")->index]!=-1)
			{
				//printf("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
				st=pop(st);
				break;
			}
			else
			{
				printf("UNEXPECTED TOKEN.\n");
				printf("%s %d",nextToken->lexeme,nextToken->LN);
				error_list* new_error=(error_list*)malloc(sizeof(error_list));
				new_error->tk=nextToken;
				new_error->next=errors;
				errors=new_error;
				nextToken=getNextToken();
				validateLexError(nextToken);
			}
		}
		if((nextToken==NULL) && peek(st)!=bottom)
		{
			printf("REACHED END OF PROGRAM WITHOUT COMPLETE PARSE TREE GENERATION\n");
			error_list* new_error=(error_list*)malloc(sizeof(error_list));
			new_error->tk=nextToken;
			new_error->next=errors;
			errors=new_error;
			return errors;
		}
	}

	
	if(nextToken->index!=0)
	{
			printf("Extra Tokens Found %s %d \n",nextToken->lexeme,nextToken->LN);
			error_list* new_error=(error_list*)malloc(sizeof(error_list));
			new_error->tk=nextToken;
			new_error->next=errors;
			errors=new_error;
	}
	else
	{
		printf("Parsing complete...");
	}
	return errors;
}
