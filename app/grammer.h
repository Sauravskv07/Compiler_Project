#define MAX_RULES 100

struct
{
	int index;
	Type tag;
	struct Node* next;
}Node;

typedef struct
{
	char name[20];
	struct Node* node;
}Element;

struct grammer_table
{
	int num_rules;
	Element grammer[MAX_RULES];
};
