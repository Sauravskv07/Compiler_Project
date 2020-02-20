# define MAX_RULES 10


typedef struct rule_rhs{
    ht_item *node;
    struct rule_rhs *next;
} rule_rhs;

typedef struct {
    ht_item *lhs;
    rule_rhs* key;
} rules_table;


rules_table rules[MAX_RULES];

int parse(char *fileName,ht_hash_table* mapping_table);
int addLine(char *line, int index);
void printRules();