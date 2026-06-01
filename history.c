#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

History *init_history() {
    History *h = (History *)malloc(sizeof(History));
    h->head = NULL;
    h->size = 0;
    return h;
}

void add_history(History *h, char *str) {
    Item *newItem = (Item *)malloc(sizeof(Item));
    newItem->id = h->size + 1;
    newItem->str = strdup(str);
    newItem->next = h->head;
    h->head = newItem;
    h->size++;
}

char *get_history(History *h, int id) {
    Item *curr = h->head;
    while (curr) {
        if (curr->id == id) return curr->str;
        curr = curr->next;
    }
    return NULL;
}

void print_history(History *h) {
    Item *curr = h->head;
    while (curr) {
        printf("%d: %s\n", curr->id, curr->str);
        curr = curr->next;
    }
}

void free_history(History *h) {
    Item *curr = h->head;
    while (curr) {
        Item *tmp = curr;
        curr = curr->next;
        free(tmp->str);
        free(tmp);
    }
    free(h);
}
