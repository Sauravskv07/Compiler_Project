# define MAX_RULES 200

typedef struct rule_rhs{
    ht_item *node;
    struct rule_rhs *next;
} rule_rhs;

typedef struct {
    ht_item *lhs;
    rule_rhs* key;
} rules_table;

rules_table rules[MAX_RULES];
int rule_count;

int parse(char *fileName);
int addLine(char *line, int index);
void printRules();
void printRule(int i);
