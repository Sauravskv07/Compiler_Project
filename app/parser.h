#define MAX_RHS 10

treenode *parse_tree;
stack *parse_stack;

struct error_list{
	struct error_list* next;
	Token* tk;
}errors;

struct error_list* parse(treenode* tn, stack *st);

