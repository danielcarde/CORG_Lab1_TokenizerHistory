#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

int main(void) {
    History *history = init_history();
    if (!history) { fputs("Unable to allocate history.\n", stderr); return 1; }
    char input[256];

    printf("Simple Tokenizer. Type 'exit' to quit.\n");

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0'; // strip newline

        if (strcmp(input, "exit") == 0) break;
        if (strcmp(input, "history") == 0) {
            print_history(history);
            continue;
        }

        // recall from history (!id)
        if (input[0] == '!') {
            int id = atoi(&input[1]);
            char *cmd = get_history(history, id);
            if (cmd) {
                printf("Recalled: %s\n", cmd);
                char **tokens = tokenize(cmd);
                if (!tokens) { fputs("Unable to allocate tokens.\n", stderr); free_history(history); return 1; }
                print_tokens(tokens);
                free_tokens(tokens);
            } else {
                printf("No history with id %d\n", id);
            }
            continue;
        }

        if (!add_history(history, input)) {
            fputs("Unable to save history.\n", stderr);
            free_history(history);
            return 1;
        }

        char **tokens = tokenize(input);
        if (!tokens) { fputs("Unable to allocate tokens.\n", stderr); free_history(history); return 1; }
        print_tokens(tokens);
        free_tokens(tokens);
    }

    free_history(history);
    return 0;
}
