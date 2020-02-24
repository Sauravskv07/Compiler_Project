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
#include <stdlib.h>

int endReached=0;
int j_pointer=0;
int state=1;
int LN=1;
int backPointer=0;
int forwardPointer=0;

FILE * getStream(FILE* fp)
{
	int i=0;
	for(;i<(backPointer-forwardPointer);i++)
	{
		buffer[i]=buffer[backPointer+i];
		//printf("%d  %c \n",i,buffer[i]);
	}

	for(;i<MAX_BUFF_SIZE;i++)
	{
		buffer[i]=getc(fp);
		//printf("%d %c\n",i,buffer[i]);
		if(buffer[i]==EOF)
		{
			buffer[i]='\0';
			//printf("Reached End of the Program\n");
			break;
		}
		//printf("%d  %c \n",i,buffer[i]);
	}	
}

Token* createToken(int index,int bp,int fp, int ln)
{
	Token* temp=(Token*) malloc(sizeof(Token));
	
	//printf("backpointer= %d forwardPointer= %d",bp,fp);
	int i=bp;	

	for(;i<=fp;i++)
		temp->lexeme[i-bp]=buffer[i];
	temp->lexeme[i]='\0';

	temp->index=index;
	temp->LN=ln;
	temp->val.i_val=0;

	if(index==ht_search(mapping_table,"ID")->index)
	{
		if(ht_search(keyword_table,temp->lexeme))
		{	
			j_pointer=0;
			while(temp->lexeme[j_pointer])
			{
				token[j_pointer]=toupper(temp->lexeme[j_pointer++]);
			}
			token[j_pointer]=0;			

			temp->index=ht_search(mapping_table,token)->index;	
		}
		else
		{
			if(strlen(temp->lexeme)>20)
				temp->index=-1;
		}
	}

	if(index==ht_search(mapping_table,"NUM")->index)
	{	
		temp->val.i_val = atoi(temp->lexeme);
	}

	else if(index==ht_search(mapping_table,"RNUM")->index)
	{
		temp->val.f_val = atof(temp->lexeme);
	}
	
	printf("LEXEME=  %s  VALUE=  %d  LINE NUMBER=  %d  TYPE=  %d\n",temp->lexeme,temp->val,temp->LN,temp->index);
	return temp;
}

Token* getNextToken()
{
	state=1;

	if(endReached==1)
		return NULL;
		
	while(1)
	{
		forwardPointer++;
	
		if(forwardPointer==MAX_BUFF_SIZE)
		{	
			fp=getStream(fp);
		}
		//printf("forward pointer = %d\n",forwardPointer);
		character_read=buffer[forwardPointer];

		//printf("State = %d  Character Read = %c\n",state,character_read);
				
		switch(state)
		{
			case 1:
			{
				backPointer=forwardPointer;
				
				if(character_read==0)
				{
					endReached=1;
					return createToken(ht_search(mapping_table,"$")->index,0,0,LN);
				}
				else if(character_read=='(')
				{
					return createToken(ht_search(mapping_table,"BO")->index,backPointer,forwardPointer,LN);
				}
				else if(character_read==')')
				{
					return createToken(ht_search(mapping_table,"BC")->index,backPointer,forwardPointer,LN);
				}
				else if(character_read=='+')
				{
					return createToken(ht_search(mapping_table,"PLUS")->index,backPointer,forwardPointer,LN);
				}
				else if(character_read=='-')
				{
					return createToken(ht_search(mapping_table,"MINUS")->index,backPointer,forwardPointer,LN);
				}
				else if(character_read=='[')
				{
					return createToken(ht_search(mapping_table,"SQBO")->index,backPointer,forwardPointer,LN);
				}
				else if(character_read==']')
				{
					return createToken(ht_search(mapping_table,"SQBC")->index,backPointer,forwardPointer,LN);
				}
				else if(character_read=='\n')
				{
					state=1;
					LN++;
				}
				else if(character_read==':')
				{
					state=35;
				}
				else if(character_read=='/')
				{
					return createToken(ht_search(mapping_table,"DIV")->index,backPointer,forwardPointer,LN);
				}
				else if(character_read==';')
				{
					return createToken(ht_search(mapping_table,"SEMICOL")->index,backPointer,forwardPointer,LN);
				}
				else if(character_read=='<')
				{
					state=38;
				}
				else if(character_read=='>')
				{
					state=42;
				}
				else if(character_read=='.')
				{
					state=47;
				}
				else if(character_read==' ' || character_read=='\t')
				{
					state=31;
				}
				else if(character_read=='=')
				{
					state=21;
				}				
				else if(character_read=='!')
				{
					state=18;
				}

				else if(('a'<=character_read && character_read<='z') || ('A'<=character_read && character_read<='Z'))
				{
					state=15;
				}
				else if(character_read=='*')
				{
					state=24;
				}
				else if('0'<=character_read && character_read<='9')
				{
					state=2;
				}
				break;
					
			}
			case 35:
			{
				if(character_read=='=')
				{
					return createToken(ht_search(mapping_table,"ASSIGNOP")->index,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"COLON")->index,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 38:
			{
				if(character_read=='<')
				{
					state=43;
				}
				else if(character_read=='=')
				{
					return createToken(ht_search(mapping_table,"LE")->index,backPointer,forwardPointer,LN);
				}
				else
				{	
					forwardPointer--;
					return createToken(ht_search(mapping_table,"LT")->index,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 43:
			{

				if(character_read=='<')
				{
					return createToken(ht_search(mapping_table,"DRIVERDEF")->index,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"DEF")->index,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 42:
			{
				if(character_read=='>')
				{
					state=46;
				}
				else if(character_read=='=')
				{
					return createToken(ht_search(mapping_table,"GE")->index,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"GT")->index,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 46:
			{

				if(character_read=='>')
				{
					return createToken(ht_search(mapping_table,"DRIVERENDDEF")->index,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"ENDDEF")->index,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 47:
			{
				if(character_read=='.')
				{
					return createToken(ht_search(mapping_table,"RANGEOP")->index,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(-1,backPointer,forwardPointer,LN);
				}
				break;
			}

			case 31:
			{
				if(character_read==' ' ||  character_read=='\t')
				{
					state=31;
				}
				else
				{
					state=1;
					forwardPointer--;
				}
				break;
			}

			case 21:
			{
				if(character_read=='=')
				{
					return createToken(ht_search(mapping_table,"EQ")->index,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(-1,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 18:
			{
				if(character_read=='=')
				{
					return createToken(ht_search(mapping_table,"NE")->index,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(-1,backPointer,forwardPointer,LN);
				}
				break;
			}

			case 15:
			{
				//printf("%c\n",character_read);
				if(character_read=='_' ||('a'<=character_read && character_read<='z') || ('A'<=character_read && character_read<='Z')|| ('0'<= character_read && character_read<='9'))
				{
					state=15;
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"ID")->index,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 24:
			{
				if(character_read=='*')
				{
					state=26;
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"MUL")->index,backPointer,forwardPointer,LN);
				}
				break;
			}	
			case 26:
			{
				if(character_read=='*')
				{
					state=27;
				}
				else
				{
					if(character_read=='\n')
						LN++;
					state=26;
				}
				break;
			}
			case 27:
			{
				if(character_read=='*')
				{
					state=1;
				}
				else
				{
					if(character_read=='\n')
						LN++;
					state=26;
				}

				break;
			}

			case 2:
			{
				if('0'<= character_read && character_read<='9')
				{
					state=2;
				}
				else if(character_read=='.')
				{
					state=4;
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"NUM")->index,backPointer,forwardPointer,LN);		
				}
				break;
			}
			case 4:
			{
				if(character_read=='.')
				{
					forwardPointer-=2;
					return createToken(ht_search(mapping_table,"NUM")->index,backPointer,forwardPointer,LN);
				}
				else if('0'<= character_read && character_read<='9')
				{
					state=6;
				}		
				else
				{
					forwardPointer-=2;
					return createToken(ht_search(mapping_table,"NUM")->index,backPointer,forwardPointer,LN);
				}		
				break;
			}
			case 6:
			{
				if('0'<= character_read && character_read<='9')
				{
					state=6;
				}
				else if(character_read=='e' || character_read=='E')
				{
					state=8;
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"RNUM")->index,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 8:
			{
				if(character_read=='+' || character_read=='-')
				{
					state=10;
				}
				else if('0'<= character_read && character_read<='9')
				{
					state=11;
				}
				else
				{
					forwardPointer-=2;
					return createToken(ht_search(mapping_table,"RNUM")->index,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 10:
			{
				if('0'<= character_read && character_read<='9')
				{
					state=11;
				}
				else
				{
					forwardPointer-=3;
					return createToken(ht_search(mapping_table,"RNUM")->index,backPointer,forwardPointer,LN);
				}
				break;			
			}

			case 11:
			{
				if('0'<= character_read && character_read<='9')
				{
					state=11;
				}
				else
				{
					forwardPointer--;
					return createToken(ht_search(mapping_table,"RNUM")->index,backPointer,forwardPointer,LN);
				}			
				break;
			}
		}
	}	
}




