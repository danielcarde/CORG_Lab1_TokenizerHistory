#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

int main() {
    History *history = init_history();
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
                print_tokens(tokens);
                free_tokens(tokens);
            } else {
                printf("No history with id %d\n", id);
            }
            continue;
        }

        add_history(history, input);

        char **tokens = tokenize(input);
        print_tokens(tokens);
        free_tokens(tokens);
    }

    free_history(history);
    return 0;
}
