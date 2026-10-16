#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "history.h"

History *init_history(void) {
    History *h = malloc(sizeof(*h));
    if (!h) return NULL;
    h->head = NULL; h->size = 0;
    return h;
}
int add_history(History *h, const char *str) {
    if (!h || !str || h->size == INT_MAX) return 0;
    Item *item = malloc(sizeof(*item));
    if (!item) return 0;
    size_t length = strlen(str);
    item->str = malloc(length + 1);
    if (!item->str) { free(item); return 0; }
    memcpy(item->str, str, length + 1);
    item->id = h->size + 1;
    item->next = h->head;
    h->head = item; h->size++;
    return 1;
}
char *get_history(History *h, int id) {
    if (!h) return NULL;
    for (Item *item = h->head; item; item = item->next)
        if (item->id == id) return item->str;
    return NULL;
}
void print_history(History *h) {
    if (!h) return;
    for (Item *item = h->head; item; item = item->next) printf("%d: %s\n", item->id, item->str);
}
void free_history(History *h) {
    if (!h) return;
    Item *item = h->head;
    while (item) {
        Item *next = item->next;
        free(item->str); free(item); item = next;
    }
    free(h);
}
