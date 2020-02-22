
typedef union node
{
	Token *token;
	NonTerm *nonterm;
}node;

typedef struct treenode
{
	node *data;
	treenode *child;
	treenode *right;
	treenode *parent;
	Type tag;
}treenode;

typedef struct block
{
	node *data;
	Type tag;
}block;

typedef struct stack
{
	block* data;
	block * next;
	block *prev;
}stack;

stack *st = NULL;
block *pop(stack *st);
block *push(stack *st,block *b);
block *peek(stack *st);

treenode *root = NULL;
treenode *insertAsChild(treenode *parent, node *child, Type tag);
treenode *insertAsNextSibling(treenode *child, node *right, Type tag);
treenode *getRoot(treenode *child);
void *printTraversal(treenode *root);
