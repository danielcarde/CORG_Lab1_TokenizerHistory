#ifndef HISTORY_H
#define HISTORY_H

typedef struct s_item {
    int id;
    char *str;
    struct s_item *next;
} Item;

typedef struct {
    Item *head;
    int size;
} History;

History *init_history();
void add_history(History *h, char *str);
char *get_history(History *h, int id);
void print_history(History *h);
void free_history(History *h);

#endif
