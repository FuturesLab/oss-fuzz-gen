// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_init at janet.c:33101:13 in janet.h
// janet_table_weakk at janet.c:33126:13 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_table_weakkv at janet.c:33136:13 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>

#define MAX_CAPACITY 1024

static void fuzz_janet_table_weakv(int32_t capacity) {
    JanetTable *table = janet_table_weakv(capacity);
    if (table) {
        // Optionally perform operations on the table
    }
}

static void fuzz_janet_table_init(int32_t capacity) {
    JanetTable table;
    JanetTable *result = janet_table_init(&table, capacity);
    if (result) {
        // Optionally perform operations on the table
    }
}

static void fuzz_janet_table_weakk(int32_t capacity) {
    JanetTable *table = janet_table_weakk(capacity);
    if (table) {
        // Optionally perform operations on the table
    }
}

static void fuzz_janet_table_init_raw(int32_t capacity) {
    JanetTable table;
    if (capacity >= 0 && capacity <= MAX_CAPACITY) {
        JanetTable *result = janet_table_init_raw(&table, capacity);
        if (result) {
            // Optionally perform operations on the table
        }
    }
}

static void fuzz_janet_table(int32_t capacity) {
    JanetTable *table = janet_table(capacity);
    if (table) {
        // Optionally perform operations on the table
    }
}

static void fuzz_janet_table_weakkv(int32_t capacity) {
    JanetTable *table = janet_table_weakkv(capacity);
    if (table) {
        // Optionally perform operations on the table
    }
}

int LLVMFuzzerTestOneInput_155(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) {
        return 0;
    }

    int32_t capacity = *((int32_t *)Data);

    janet_init();

    fuzz_janet_table_weakv(capacity);
    fuzz_janet_table_init(capacity);
    fuzz_janet_table_weakk(capacity);
    fuzz_janet_table_init_raw(capacity);
    fuzz_janet_table(capacity);
    fuzz_janet_table_weakkv(capacity);

    janet_deinit();

    return 0;
}