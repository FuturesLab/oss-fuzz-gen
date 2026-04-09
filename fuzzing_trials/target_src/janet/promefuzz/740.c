// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_table at janet.c:33121:13 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_table_put at janet.c:33237:6 in janet.h
// janet_table_rawget at janet.c:33212:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_table_remove at janet.c:33222:7 in janet.h
// janet_table_get at janet.c:33179:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_table_rawget at janet.c:33212:7 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

static JanetTable *initialize_table(int32_t capacity) {
    JanetTable *table = janet_table(capacity);
    return table;
}

static Janet random_janet_value(const uint8_t *Data, size_t Size, size_t *offset) {
    if (*offset + sizeof(uint64_t) <= Size) {
        uint64_t value = *(const uint64_t *)(Data + *offset);
        *offset += sizeof(uint64_t);
        return janet_wrap_number((double)value);
    }
    return janet_wrap_nil();
}

int LLVMFuzzerTestOneInput_740(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    janet_init();

    size_t offset = 0;
    int32_t capacity = *(const int32_t *)(Data + offset);
    offset += sizeof(int32_t);

    JanetTable *table = initialize_table(capacity);
    if (!table) {
        janet_deinit();
        return 0;
    }

    while (offset < Size) {
        Janet key = random_janet_value(Data, Size, &offset);
        Janet value = random_janet_value(Data, Size, &offset);

        janet_table_put(table, key, value);

        Janet retrieved_value = janet_table_rawget(table, key);
        (void)retrieved_value;

        Janet wrapped_table = janet_wrap_table(table);
        (void)wrapped_table;

        Janet removed_value = janet_table_remove(table, key);
        (void)removed_value;

        Janet get_value = janet_table_get(table, key);
        (void)get_value;

        JanetTable *unwrapped_table = janet_unwrap_table(wrapped_table);
        if (unwrapped_table) {
            (void)janet_table_rawget(unwrapped_table, key);
        }
    }

    janet_deinit();
    return 0;
}