#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c) {
    return (c == ' ' || c == '\t') && c != '\0';
}

int non_space_char(char c) {
    return (c != ' ' && c != '\t' && c != '\0');
}

char *token_start(char *s) {
    while (*s && space_char(*s)) s++;
    return *s ? s : NULL;
}

char *token_terminator(char *s) {
    while (*s && non_space_char(*s)) s++;
    return s;
}

int count_tokens(char *s) {
    int count = 0;
    char *p = s;
    while ((p = token_start(p))) {
        count++;
        p = token_terminator(p);
    }
    return count;
}

char *copy_str(char *inStr, short len) {
    char *copy = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        copy[i] = inStr[i];
    }
    copy[len] = '\0';
    return copy;
}

char **tokenize(char *s) {
    int tokens = count_tokens(s);
    char **arr = (char **)malloc((tokens + 1) * sizeof(char *));
    int i = 0;
    char *p = s;

    while ((p = token_start(p))) {
        char *end = token_terminator(p);
        arr[i++] = copy_str(p, end - p);
        p = end;
    }
    arr[i] = NULL;
    return arr;
}

void print_tokens(char **tokens) {
    for (int i = 0; tokens[i]; i++) {
        printf("Token %d: %s\n", i + 1, tokens[i]);
    }
}

void free_tokens(char **tokens) {
    for (int i = 0; tokens[i]; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
