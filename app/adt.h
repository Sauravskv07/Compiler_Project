typedef union node
{
	Token *token;
	ht_item *nonterm;
}node;

typedef struct treenode
{
	node *data;
	struct treenode *child;
	struct treenode *right;
	struct treenode *parent;
	Type tag;
}treenode;

typedef struct stack
{
	ht_item *data;
	struct stack *next;
	struct stack *prev;
}stack;

stack *pop(stack *st);
stack *push(stack *st,ht_item *b);
ht_item *peek(stack *st);

treenode *root = NULL;

treenode *insertAsChild(treenode *parent, node *child, Type tag);
treenode *insertAsNextSibling(treenode *child, node *right, Type tag);
treenode *getRoot(treenode *child);
void printTraversal(treenode *root);
