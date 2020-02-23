#define MAX_RHS 10

treenode *parse_tree;
stack *parse_stack;

struct error_list{
	struct error_list* next;
	Token* tk;
}errors;

void program(treenode* tn, stack* st);
void moduleDeclarations(treenode* tn, stack* st);
void moduleDeclaration(treenode* tn, stack* st);
void otherModules(treenode* tn, stack* st);
void driverModule(treenode* tn, stack* st);
void module(treenode* tn, stack* st);
void ret(treenode* tn, stack* st);
void input_plist(treenode* tn, stack* st);
void N1(treenode* tn, stack* st);
void output_plist(treenode* tn, stack* st);
void N2(treenode* tn, stack* st);
void dataType(treenode* tn, stack* st);
void range_arrays(treenode* tn, stack* st);
void type(treenode* tn, stack* st);
void moduleDef(treenode* tn, stack* st);
void statements(treenode* tn, stack* st);
void statement(treenode* tn, stack* st);
void ioStmt(treenode* tn, stack* st);
void boolConstt(treenode* tn, stack* st);
void var_id_num(treenode* tn, stack* st);
void var(treenode* tn, stack* st);
void whichId(treenode* tn, stack* st);
void simpleStmt(treenode* tn, stack* st);
void assignmentStmt(treenode* tn, stack* st);
void whichStmt(treenode* tn, stack* st);
void lvalueIDStmt(treenode* tn, stack* st);
void lvalueARRStmt(treenode* tn, stack* st);
void index(treenode* tn, stack* st);
void moduleReuseStmt(treenode* tn, stack* st);
void optional(treenode* tn, stack* st);
void idList(treenode* tn, stack* st);
void N3(treenode* tn, stack* st);
void expression(treenode* tn, stack* st);
void U(treenode* tn, stack* st);
void new_NT(treenode* tn, stack* st);
void unary_op(treenode* tn, stack* st);
void arithmeticOrBooleanExpr(treenode* tn, stack* st);
void AnyTerm(treenode* tn, stack* st);
void N7(treenode* tn, stack* st);
void N8(treenode* tn, stack* st);
void arithmeticExpr(treenode* tn, stack* st);
void N4(treenode* tn, stack* st);
void term(treenode* tn, stack* st);
void N5(treenode* tn, stack* st);
void factor(treenode* tn, stack* st);
void op1(treenode* tn, stack* st);
void op2(treenode* tn, stack* st);
void logicalOp(treenode* tn, stack* st);
void relationalOp(treenode* tn, stack* st);
void declareStmt(treenode* tn, stack* st);
void conditionalStmt(treenode* tn, stack* st);
void caseStmts(treenode* tn, stack* st);
void N9(treenode* tn, stack* st);
void value(treenode* tn, stack* st);
void Default(treenode* tn, stack* st);
void iterativeStmt(treenode* tn, stack* st);
void range(treenode* tn, stack* st);

struct error_list* parse(treenode* tn, stack *st);

