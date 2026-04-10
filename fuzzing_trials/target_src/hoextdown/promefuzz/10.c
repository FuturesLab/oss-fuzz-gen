// This fuzz driver is generated for library hoextdown, aiming to fuzz the following functions:
// hoedown_hash_new at hash.c:131:1 in hash.h
// hoedown_malloc at buffer.c:9:1 in buffer.h
// hoedown_hash_new at hash.c:131:1 in hash.h
// hoedown_hash_add at hash.c:179:1 in hash.h
// hoedown_hash_find at hash.c:206:1 in hash.h
// hoedown_hash_free at hash.c:161:1 in hash.h
// hoedown_stack_uninit at stack.c:24:1 in stack.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "stack.h"
#include "hash.h"

static hoedown_hash* create_dummy_hash() {
    return hoedown_hash_new(10);
}

static void dummy_destruct(void *value) {
    free(value);
}

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test hoedown_malloc
    void *memory = hoedown_malloc(Size);
    if (memory) {
        memset(memory, 0, Size);
        free(memory);
    }

    // Test hoedown_hash_new and hoedown_hash_free
    hoedown_hash *hash = hoedown_hash_new(Size);
    if (hash) {
        // Test hoedown_hash_add
        char *key = malloc(Size);
        if (key) {
            memcpy(key, Data, Size);
            void *value = malloc(1); // Dummy value
            if (value) {
                hoedown_hash_add(hash, key, Size, value, dummy_destruct);
            }
            free(key);
        }

        // Test hoedown_hash_find
        hoedown_hash_find(hash, (char *)Data, Size);

        // Cleanup hash
        hoedown_hash_free(hash);
    }

    // Test hoedown_stack_uninit
    hoedown_stack stack;
    stack.item = malloc(sizeof(void*) * 10);
    stack.size = 0;
    stack.asize = 10;
    hoedown_stack_uninit(&stack);

    return 0;
}