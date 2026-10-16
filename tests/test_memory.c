#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static int remaining = -1;
static int allocations = 0;
static void *test_malloc(size_t size) {
    if (remaining == 0) return NULL;
    if (remaining > 0) remaining--;
    void *p = malloc(size);
    if (p) allocations++;
    return p;
}
static void test_free(void *p) {
    if (p) allocations--;
    free(p);
}
#define malloc test_malloc
#define free test_free
#include "../tokenizer.c"
#include "../history.c"
#undef malloc
#undef free

int main(void) {
    char text[] = "  alpha\tbeta  ";
    char blank[] = " \t ";
    assert(count_tokens(text) == 2);
    char **tokens = tokenize(text);
    assert(tokens && !strcmp(tokens[0],"alpha") && !strcmp(tokens[1],"beta") && !tokens[2]);
    free_tokens(tokens);
    tokens = tokenize(blank); assert(tokens && !tokens[0]); free_tokens(tokens);
    assert(tokenize(NULL) == NULL);
    free_tokens(NULL); free_history(NULL);
    char *large = malloc(40001); assert(large);
    memset(large,'x',40000); large[40000]=0;
    char *copy = copy_str(large,40000);
    assert(copy && strlen(copy)==40000); test_free(copy); free(large);
    assert(copy_str("x",SIZE_MAX)==NULL);
    assert(allocations==0);

    for(int limit=0;limit<3;limit++) {
        remaining=limit;
        assert(tokenize(text)==NULL);
        assert(allocations==0);
    }
    remaining=0; assert(init_history()==NULL);
    remaining=-1; History *h=init_history(); assert(h);
    for(int limit=0;limit<2;limit++) {
        remaining=limit;
        assert(!add_history(h,"saved"));
        assert(h->size==0 && h->head==NULL && allocations==1);
    }
    remaining=-1;
    assert(add_history(h,"first") && add_history(h,"second"));
    assert(!strcmp(get_history(h,1),"first") && !strcmp(get_history(h,2),"second"));
    assert(get_history(h,99)==NULL);
    h->size=INT_MAX; assert(!add_history(h,"overflow")); h->size=2;
    free_history(h); assert(allocations==0);
    puts("Tokenizer/history and allocation-failure checks passed");
    return 0;
}
