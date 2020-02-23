typedef union node
{
	Token *token;
	ht_item *nonterm;
}node;

typedef struct treenode
{
	node *data;
	treenode *child;
	treenode *right;
	treenode *parent;
	Type tag;
}treenode;

typedef struct stack
{
	int status;
	ht_item* data;
	ht_item * next;
	ht_item *prev;
}stack;

stack *pop(stack *st);
stack *push(stack *st,ht_item *b,int status);
stack *peek(stack *st);

treenode *insertAsChild(treenode *parent, node *child, Type tag);
treenode *insertAsNextSibling(treenode *child, node *right, Type tag);
treenode *getRoot(treenode *child);
void *printTraversal(treenode *root);
