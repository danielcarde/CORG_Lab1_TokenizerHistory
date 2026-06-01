#ifndef TOKENIZER_H
#define TOKENIZER_H

int space_char(char c);                 // true if space/tab
int non_space_char(char c);             // true if non-space
char *token_start(char *s);             // pointer to start of token
char *token_terminator(char *s);        // pointer to end of token
int count_tokens(char *s);              // count tokens
char *copy_str(char *inStr, short len); // copy substring
char **tokenize(char *s);               // return array of tokens
void print_tokens(char **tokens);       // print tokens
void free_tokens(char **tokens);        // free tokens

#endif
