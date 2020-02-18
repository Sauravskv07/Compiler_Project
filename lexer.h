//no need to know what is the index of the keyword, just need to know whether a keyword or not
//typedef enum {INTEGER,REAL, BOOLEAN, OF, ARRAY, START, AND, DECLARE,MODULE,DRIVER, PROGRAM, RECORD, TAGGED, UNION, GET_VALUE,PRINT,USE, WITH, PARAMETERS,TRUE,FALSE,TAKES, INPUT, RETURNS,AND,OR, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE} keywords;



#include <stdio.h>
#include <stdlib.h>
#define MAX_BUFF_SIZE 1000

enum Terminal {NUM,RNUM, ID, BOOLEAN, OF, ARRAY, START, AND, DECLARE,MODULE,DRIVER, PROGRAM, RECORD, TAGGED, UNION, GET_VALUE,PRINT,USE, WITH, PARAMETERS,TRUE,FALSE,TAKES, INPUT, RETURNS,OR, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE,PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, DRIVERDEF, ENDDEF, COLON, RANGEOF, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ERROR, RANGEOP, ENDDRIVERDEF} ;

enum Nonterminal {program, moduleDeclarations, moduleDeclaration, otherModules, driverModule, module, ret, input_plist, N1, output_plist, N2, dataType, range_arrays,type, moduleDef, statements, statement, ioStmt, boolConstt,var_id_num, var, whichId, simpleStmt, assignmentStmt, whichStmt, lvalueIDStatement, lvaluearrStatement, index, moduleResuseStatement, optional, idList, N3, expression,arithmeticOrBooleanExpr ,U ,new_NT, unary_op, AnyTerm, N7, N8, arithmeticExpr, N4, N5, term, factor, op1, op2, logicalOp, relationalOp, declareStmt, conditionalStmt, caseStmts, N9, value, Default, iterativeStmt, range  };

typedef enum{KEYWORD, SYMBOL, NONTERMINAL} Type;

typedef union
{
	int i_val;
	float f_val;
}Value;

typedef struct
{
	char lexeme[21];
	Value val;
	enum Terminal token_type;
	int LN;
} Token;

FILE* fp;
char buffer[MAX_BUFF_SIZE];
int forwardPointer;
int backPointer;
int state;
char character_read;
int LN;
enum Terminal token_type;

FILE * getStream(FILE* fp);
Token* createToken(int type,int bp,int fp, int ln);
Token* getNextToken();

