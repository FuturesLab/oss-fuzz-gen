// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_table_put at janet.c:33237:6 in janet.h
// janet_table_get at janet.c:33179:7 in janet.h
// janet_table_get_ex at janet.c:33200:7 in janet.h
// janet_table_rawget at janet.c:33212:7 in janet.h
// janet_table_remove at janet.c:33222:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_table at janet.c:33121:13 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static JanetTable *initialize_table(int32_t capacity) {
    JanetTable *table = janet_table(capacity);
    return table;
}

static Janet create_janet_key(const uint8_t *Data, size_t Size) {
    // Create a Janet key from the input data
    Janet key;
    if (Size >= sizeof(uint64_t)) {
        key.u64 = *((uint64_t *)Data);
    } else {
        key.u64 = 0; // Default key if data is insufficient
    }
    return janet_wrap_number((double)key.u64); // Ensure key is a valid Janet type
}

static Janet create_janet_value(const uint8_t *Data, size_t Size) {
    // Create a Janet value from the input data
    Janet value;
    if (Size >= sizeof(double)) {
        value.number = *((double *)Data);
    } else {
        value.u64 = 0; // Default value if data is insufficient
    }
    return janet_wrap_number(value.number); // Ensure value is a valid Janet type
}

int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet VM
    janet_init();

    // Initialize a JanetTable
    JanetTable *table = initialize_table(10);

    // Create a key and a value from the input data
    Janet key = create_janet_key(Data, Size);
    Janet value = create_janet_value(Data, Size);

    // Fuzz janet_table_put
    janet_table_put(table, key, value);

    // Fuzz janet_table_get
    Janet result_get = janet_table_get(table, key);

    // Fuzz janet_table_get_ex
    JanetTable *which = NULL;
    Janet result_get_ex = janet_table_get_ex(table, key, &which);

    // Fuzz janet_table_rawget
    Janet result_rawget = janet_table_rawget(table, key);

    // Fuzz janet_table_remove
    Janet result_remove = janet_table_remove(table, key);

    // Fuzz janet_wrap_table
    Janet wrapped_table = janet_wrap_table(table);

    // Cleanup
    janet_deinit();

    return 0;
}