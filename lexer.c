#include "lexer.h"


state=1;
LN=1;
backPointer=0;
forwardPointer=0;

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
		if(buffer[i]==EOF)
		{
			buffer[i]='\0';
			break;
		}
		//printf("%d  %c \n",i,buffer[i]);
	}	
}

Token* createToken(int type,int bp,int fp, int ln)
{
	Token* temp=(Token*) malloc(sizeof(Token));
	
	//printf("backpointer= %d forwardPointer= %d",bp,fp);
	int i=bp;	

	for(;i<=fp;i++)
		temp->lexeme[i-bp]=buffer[i];
	temp->lexeme[i]='\0';

	temp->token_type=type;
	temp->LN=ln;
	temp->val.i_val=0;

	if(type==ID)
	{}

	if(type==NUM)
	{	
	
	}

	else if(type==RNUM)
	{}

	return temp;
}

Token* getNextToken()
{
	state=1;

	while(1)
	{
		forwardPointer++;
	
		if(forwardPointer==MAX_BUFF_SIZE)
		{	
			fp=getStream(fp);
		}
		//printf("forward pointer = %d\n",forwardPointer);
		character_read=buffer[forwardPointer];

		printf("State = %d  Character Read = %c\n",state,character_read);
				
		switch(state)
		{
			case 1:
			{
				backPointer=forwardPointer;
				
				if(character_read=='\0')
				{
					return NULL;
				}
				if(character_read=='(')
				{
					return createToken(BO,backPointer,forwardPointer,LN);
				}
				else if(character_read==')')
				{
					return createToken(BC,backPointer,forwardPointer,LN);
				}
				else if(character_read=='+')
				{
					return createToken(PLUS,backPointer,forwardPointer,LN);
				}
				else if(character_read=='-')
				{
					return createToken(MINUS,backPointer,forwardPointer,LN);
				}
				else if(character_read=='[')
				{
					return createToken(SQBO,backPointer,forwardPointer,LN);
				}
				else if(character_read==']')
				{
					return createToken(SQBC,backPointer,forwardPointer,LN);
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
					return createToken(DIV,backPointer,forwardPointer,LN);
				}
				else if(character_read==';')
				{
					return createToken(SEMICOL,backPointer,forwardPointer,LN);
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
					return createToken(ASSIGNOP,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(COLON,backPointer,forwardPointer,LN);
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
					return createToken(LE,backPointer,forwardPointer,LN);
				}
				else
				{	
					forwardPointer--;
					return createToken(LT,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 43:
			{

				if(character_read=='<')
				{
					return createToken(DRIVERDEF,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(DEF,backPointer,forwardPointer,LN);
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
					return createToken(GE,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(GT,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 46:
			{

				if(character_read=='>')
				{
					return createToken(ENDDRIVERDEF,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(ENDDEF,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 47:
			{
				if(character_read=='.')
				{
					return createToken(RANGEOP,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(ERROR,backPointer,forwardPointer,LN);
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
					return createToken(EQ,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(ERROR,backPointer,forwardPointer,LN);
				}
				break;
			}
			case 18:
			{
				if(character_read=='=')
				{
					return createToken(NE,backPointer,forwardPointer,LN);
				}
				else
				{
					forwardPointer--;
					return createToken(ERROR,backPointer,forwardPointer,LN);
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
					return createToken(ID,backPointer,forwardPointer,LN);
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
					return createToken(MUL,backPointer,forwardPointer,LN);
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
					return createToken(NUM,backPointer,forwardPointer,LN);			
				}
				break;
			}
			case 4:
			{
				if(character_read=='.')
				{
					forwardPointer-=2;
					return createToken(NUM,backPointer,forwardPointer,LN);
				}
				else if('0'<= character_read && character_read<='9')
				{
					state=6;
				}		
				else
				{
					forwardPointer--;
					return createToken(NUM,backPointer,forwardPointer,LN);
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
					return createToken(RNUM,backPointer,forwardPointer,LN);
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
					return createToken(RNUM,backPointer,forwardPointer,LN);
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
					return createToken(RNUM,backPointer,forwardPointer,LN);
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
					return createToken(RNUM,backPointer,forwardPointer,LN);
				}			
				break;
			}
		}
	}	
}




