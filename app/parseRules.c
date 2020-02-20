#include "lexer.h"
#include "hash_table.h"
#include "parseRules.h"
#include <string.h>
#include <stdlib.h>

int parse(char *fileName,ht_hash_table* mapping_table)
{

	int i=0;
	FILE* rules_file=fopen(fileName,"r");	
	char *line;

    	if (rules_file == NULL)
	{
		printf("UNABLE TO OPEN FILE RULES.TXT");
        	exit(EXIT_FAILURE);
	}

	while (fgets(line, 50, rules_file)!=NULL) {
        	line[strcspn(line, "\n")] = 0;
		i = addLine(line,i);
		printf("%s", line);
    	}

	fclose(rules_file);

	printf("Rules parsing Successful\n");
	return 0;
}
int addLine(char *line, int index)
{
	char *ld = strtok (line," -");
	rules[index].lhs = ht_search(mapping_table, ld);
	if(rules[index].lhs==NULL)
	{return index++;}
	index++;
	rule_rhs* t=NULL;
	rule_rhs* term;
	ht_item* temp;
	char *nd = strtok (NULL," <>");
	while(nd!=NULL)
	{
		if(strlen(nd)==1&&nd[0]=='|')
		{
			rules[index].lhs = ht_search(mapping_table, ld);
			t=NULL;
			index++;
		}
		else
		{
			temp = ht_search(mapping_table, nd);
			if(temp==NULL)
			{return index++;}
			term = malloc(sizeof(rule_rhs));
			term->node = temp;
			term->next = NULL;
			if(t==NULL)
			{rules[index].key = term;t=rules[index].key;}
			else
			{t->next = term;t=term;}
		}
		char *nd = strtok (NULL," <>");
	}
	
	return index;
}
void printRules()
{
	for(int i=0;i<MAX_RULES;i++)
	{
		printf("%s",rules[i].lhs->key);
	}
}