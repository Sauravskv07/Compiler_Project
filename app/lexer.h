#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_BUFF_SIZE 1000
#define MAX_SIZE_MAPPING_TABLE 200


typedef enum{KEYWORD,TERMINAL, NONTERMINAL} Type;

typedef union
{
	int i_val;
	float f_val;
}Value;

typedef struct
{
	char lexeme[21];
	Value val;
	int index;
	int LN;
} Token;

FILE* fp;
char buffer[MAX_BUFF_SIZE];
int forwardPointer;
int backPointer;
int state;
char character_read;
int LN;
char token[20];
int j_pointer;

FILE * getStream(FILE* fp);
Token* createToken(int type,int bp,int fp, int ln);
Token* getNextToken();

