#define MAX_RHS 10

typedef struct error_list{
	struct error_list* next;
	Token* tk;
}error_list;

error_list* errors;

error_list* parseTree();

