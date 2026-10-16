# C Tokenizer and Command History

Academic C project by Daniel Cardenas. Splits whitespace-delimited input into tokens and stores commands in a linked history list.

## Build and run

Requires GCC or Clang and Make on Linux, macOS, or WSL.

```sh
make
./tokenizer
```

Enter a line to tokenize it, `history` to list saved commands, `!1` to recall history entry 1, and `exit` to quit. The console uses a 256-byte input buffer; long input is not supported as a single command. This is a tokenizer, not a command-executing shell. Quoting and escaping are not implemented.

## Memory handling

Token arrays are null-terminated. Failed allocations release partial results. History insertion reports failure without modifying the list. Copies use standard C allocation and copying rather than POSIX-only `strdup`. Callers own returned token arrays and release them with `free_tokens`; history owns saved strings and releases them with `free_history`.

## Verification

```sh
make test
make sanitize
make clean
```

Regression checks cover whitespace/empty input, long copies, size overflow, history lookup, cleanup, and failure of each allocation in multi-allocation operations. The sanitizer target enables AddressSanitizer, UndefinedBehaviorSanitizer, and leak detection. Both targets passed on Ubuntu/WSL with GCC 13.3. CI repeats these checks on Ubuntu. Tests simulate allocation failures; they do not prove every possible input safe.

## Files

- `tokenizer.c/.h`: token parsing, copying, allocation, and cleanup.
- `history.c/.h`: linked command history.
- `main.c`: interactive console.
- `tests/test_memory.c`: allocation-failure and behavior regression checks.

This repository preserves coursework provenance and is presented as an educational systems-programming exercise.
