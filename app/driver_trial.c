#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include "utils.h"
#include "parseTable.h"
#include "adt.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>

int main()
{
	num_terminals=0;
	num_nonterminals=0;


	printf("Start..\n");

	mapping_table= ht_new();
	
	keyword_table= ht_new();

	int i=0;
	char line[40];
	size_t len = 0;
	ssize_t read;

/*
	FILE* keyword_file=fopen("keywords.txt","r");	

    	if (keyword_file == NULL)
	{
		printf("UNABLE TO OPEN FILE KEYWORDS.TXT");
        	exit(EXIT_FAILURE);
	}

	while (fgets(line, 40, keyword_file)!=NULL) {
        	line[strcspn(line, "\n")] = 0;
		ht_insert(keyword_table,line, i++,KEYWORD);
		
        	//printf("%s", line);
    	}

	fclose(keyword_file);
*/
	i=0;

	FILE* terminal_file=fopen("terminals.txt","r");
	
    	if (terminal_file == NULL)
	{
		printf("UNABLE TO OPEN FILE TERMINALS.TXT");
        	exit(EXIT_FAILURE);
	}

	while (fgets(line, 40, terminal_file)!=NULL) {
        	line[strcspn(line, "\n")] = 0;
		tokensList[i]=ht_insert(mapping_table,line, i,TERMINAL);
		num_terminals++;		
		i++;
		
        	//printf("%s", line);
    	}

	fclose(terminal_file);

	FILE* nonterminal_file=fopen("nonterminals_trial.txt","r");
	
    	if (nonterminal_file == NULL)
	{
		printf("UNABLE TO OPEN FILE NONTERMINALS.TXT");
        	exit(EXIT_FAILURE);
	}
	while (fgets(line, 40, nonterminal_file)!=NULL) {
        	line[strcspn(line, "\n")] = 0;
		tokensList[i]=ht_insert(mapping_table,line, i,NONTERMINAL);
		num_nonterminals++;
		i++;
        	
    	}

	fclose(nonterminal_file);

	
	fp=(FILE*)fopen("program_trial.c","r");
	
	if(fp==NULL)
	{
		printf("Some error while opening the file");
		exit(1);
	}

	fp=getStream(fp);
	
	forwardPointer=-1;

	Token* next=NULL;
/*
	while(1)
	{	
		next=getNextToken();
		if(!next)
			break;
		
		printf("LEXEME=  %s  VALUE=  %d  LINE NUMBER=  %d  TYPE=  %d\n",next->lexeme,next->val,next->LN,next->index);
	}

	printf("Lexical Analysis Successful\n");
	
	//fclose(fp);

*/

	printf("PARSED RULES\n");

	parse("rule_trial.txt");
	
	printRules();

	ht_items_list* result;

	printf("FIRST AND FOLLOW SETS\n");

	for(int i=0;i<rule_count;i++)
	{	
		printRule(i);
		result=computeFirstofRule(rules[i].key);		
		printf("\nFirst = ");
		printmyList(result);
		result=computeFollow(rules[i].lhs);		
		printf("\nFollow = ");
		printmyList(result);
		printf("\n");		
	}

	printf("PRINTING THE PARSE TABLE\n");
	create_parse_table();
	
	print_parse_table();

	parseTree();
	
	//printf("%s",root->data->nonterm->key);
	//printf("%s",root->child->data->nonterm->key);
	//printf("%s",root->child->child->data->nonterm->key);
	//printf("%s",root->child->child->right->child->data->nonterm->key);
	//printf("%s",root->child->child->child->child->data->nonterm->key);
	printTraversal(root);

	exit(0);
}
