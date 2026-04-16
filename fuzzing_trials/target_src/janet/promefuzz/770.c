// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_weakk at janet.c:33126:13 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_weakk at janet.c:33126:13 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_clone at janet.c:33287:13 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_clear at janet.c:33278:6 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_770(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    int32_t capacity = *((int32_t *)Data);
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    // Test janet_table_weakv
    JanetTable *weakv_table = janet_table_weakv(capacity);
    if (weakv_table) {
        janet_table_deinit(weakv_table);
    }

    // Test janet_table_weakk
    JanetTable *weakk_table = janet_table_weakk(capacity);
    if (weakk_table) {
        janet_table_deinit(weakk_table);
    }

    // Create another table to test janet_table_merge_table
    JanetTable *merge_target = janet_table_weakv(capacity);
    JanetTable *merge_source = janet_table_weakk(capacity);
    if (merge_target && merge_source) {
        janet_table_merge_table(merge_target, merge_source);
        janet_table_deinit(merge_source);
    }
    if (merge_target) {
        janet_table_deinit(merge_target);
    }

    // Test janet_table_clone
    JanetTable *clone_table = janet_table_weakv(capacity);
    if (clone_table) {
        JanetTable *cloned = janet_table_clone(clone_table);
        // Do not deinit cloned as it is managed by GC
        janet_table_deinit(clone_table);
    }

    // Test janet_table_clear
    JanetTable *clear_table = janet_table_weakv(capacity);
    if (clear_table) {
        janet_table_clear(clear_table);
        janet_table_deinit(clear_table);
    }

    // Deinitialize Janet
    janet_deinit();

    return 0;
}