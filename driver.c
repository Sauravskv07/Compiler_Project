#include "lexer.h"

int main()
{
	fp=(FILE*)fopen("program.c","r");
	
	if(fp==NULL)
	{
		printf("Some error while opening the file");
		exit(1);
	}

	fp=getStream(fp);
	
	forwardPointer=-1;

	Token* next;

	while(next=getNextToken())
		printf("%s   %d  %d \n",next->lexeme,next->val,next->LN);

	printf("Lexical Analysis Successful");
	exit(0);
}
