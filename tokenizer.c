#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include "tokenizer.h"

int space_char(char c) { return c == ' ' || c == '\t'; }
int non_space_char(char c) { return c != '\0' && !space_char(c); }
char *token_start(char *s) {
    if (!s) return NULL;
    while (*s && space_char(*s)) s++;
    return *s ? s : NULL;
}
char *token_terminator(char *s) {
    if (!s) return NULL;
    while (*s && non_space_char(*s)) s++;
    return s;
}
int count_tokens(char *s) {
    int count = 0;
    char *p = s;
    while ((p = token_start(p))) {
        if (count == INT_MAX) return -1;
        count++;
        p = token_terminator(p);
    }
    return count;
}
char *copy_str(const char *inStr, size_t len) {
    if (!inStr || len == SIZE_MAX) return NULL;
    char *copy = malloc(len + 1);
    if (!copy) return NULL;
    memcpy(copy, inStr, len);
    copy[len] = '\0';
    return copy;
}
char **tokenize(char *s) {
    if (!s) return NULL;
    size_t count = 0;
    char *p = s;
    while ((p = token_start(p))) {
        if (count >= SIZE_MAX / sizeof(char *) - 1) return NULL;
        count++;
        p = token_terminator(p);
    }
    char **tokens = malloc((count + 1) * sizeof(*tokens));
    if (!tokens) return NULL;
    size_t i = 0;
    tokens[0] = NULL;
    p = s;
    while ((p = token_start(p))) {
        char *end = token_terminator(p);
        tokens[i] = copy_str(p, (size_t)(end - p));
        if (!tokens[i]) { free_tokens(tokens); return NULL; }
        tokens[++i] = NULL;
        p = end;
    }
    return tokens;
}
void print_tokens(char **tokens) {
    if (!tokens) return;
    for (size_t i = 0; tokens[i]; i++) printf("Token %zu: %s\n", i + 1, tokens[i]);
}
void free_tokens(char **tokens) {
    if (!tokens) return;
    for (size_t i = 0; tokens[i]; i++) free(tokens[i]);
    free(tokens);
}
