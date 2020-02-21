typedef struct ht_items_list{
    ht_item *node;
    struct ht_items_list *next;
} ht_items_list;

ht_items_list * computeFirst(ht_item *term,ht_item* tokensList[]);
ht_items_list * computeFollow(ht_item *term,ht_item* tokensList[]);
void printmyList(ht_items_list * lt);
