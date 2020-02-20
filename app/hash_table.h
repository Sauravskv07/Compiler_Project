# define HT_PRIME_1 2
# define HT_PRIME_2 3


typedef struct {
    char* key;
    int index;
    Type tag;
} ht_item;

typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;


ht_hash_table* mapping_table;
ht_hash_table* keyword_table;

void ht_insert(ht_hash_table* ht, const char* key, int index, Type tag);
ht_item* ht_search(ht_hash_table* ht, const char* key);
ht_hash_table* ht_new();

