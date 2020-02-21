#include "lexer.h"
#include "hash_table.h"
#include <string.h>
#include <stdlib.h>

int main()
{
	printf("Start..");

	mapping_table= ht_new();
	
	keyword_table= ht_new();

	ht_item *tokensList[MAX_SIZE_MAPPING_TABLE];

	int i=0;
	char line[40];
	size_t len = 0;
	ssize_t read;

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

	i=0;

	FILE* terminal_file=fopen("terminals.txt","r");
	
    	if (terminal_file == NULL)
	{
		printf("UNABLE TO OPEN FILE TERMINALS.TXT");
        	exit(EXIT_FAILURE);
	}

	while (fgets(line, 40, terminal_file)!=NULL) {
        	line[strcspn(line, "\n")] = 0;
		tokensList[i]=ht_insert(mapping_table,line, i++,TERMINAL);
        	//printf("%s", line);
    	}

	fclose(terminal_file);

	FILE* nonterminal_file=fopen("nonterminals.txt","r");
	
    	if (nonterminal_file == NULL)
	{
		printf("UNABLE TO OPEN FILE NONTERMINALS.TXT");
        	exit(EXIT_FAILURE);
	}
	while (fgets(line, 40, nonterminal_file)!=NULL) {
        	line[strcspn(line, "\n")] = 0;
		tokensList[i]=ht_insert(mapping_table,line, i++,NONTERMINAL);
        	//printf("%s", line);
    	}

	fclose(nonterminal_file);

	
	fp=(FILE*)fopen("program.c","r");
	
	if(fp==NULL)
	{
		printf("Some error while opening the file");
		exit(1);
	}

	fp=getStream(fp);
	
	forwardPointer=-1;

	Token* next=NULL;

	while(1)
	{	
		next=getNextToken();
		if(!next)
			break;
		
		printf("LEXEME=  %s  VALUE=  %d  LINE NUMBER=  %d  TYPE=  %d\n",next->lexeme,next->val,next->LN,next->index);
	}

	printf("Lexical Analysis Successful\n");
	//fclose(fp);
	exit(0);
}
