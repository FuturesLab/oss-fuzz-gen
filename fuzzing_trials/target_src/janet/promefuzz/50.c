// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_table at janet.c:33121:13 in janet.h
// janet_struct_begin at janet.c:32494:10 in janet.h
// janet_struct_end at janet.c:32603:16 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_table_merge_struct at janet.c:33318:6 in janet.h
// janet_table_find at janet.c:33143:10 in janet.h
// janet_struct_to_table at janet.c:32655:13 in janet.h
// janet_struct_find at janet.c:32513:16 in janet.h
// janet_table_to_struct at janet.c:33323:16 in janet.h
// janet_struct_begin at janet.c:32494:10 in janet.h
// janet_struct_end at janet.c:32603:16 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static void prepare_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

static JanetTable *initialize_table() {
    JanetTable *table = janet_table(10);
    return table;
}

static JanetStruct initialize_struct(const uint8_t *data, size_t size) {
    size_t num_pairs = size / sizeof(JanetKV);
    JanetKV *kvs = janet_struct_begin(num_pairs);
    for (size_t i = 0; i < num_pairs; i++) {
        kvs[i].key.u64 = data[i];
        kvs[i].value.u64 = data[i];
    }
    return janet_struct_end(kvs);
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetKV)) return 0;

    // Initialize the Janet VM
    janet_init();

    prepare_dummy_file(Data, Size);

    JanetTable *table = initialize_table();
    JanetStruct janetStruct = initialize_struct(Data, Size);

    // Fuzzing janet_table_merge_struct
    janet_table_merge_struct(table, janetStruct);

    // Fuzzing janet_table_find
    Janet key;
    key.u64 = Data[0];
    janet_table_find(table, key);

    // Fuzzing janet_struct_to_table
    JanetTable *newTable = janet_struct_to_table(janetStruct);

    // Fuzzing janet_struct_find
    janet_struct_find(janetStruct, key);

    // Fuzzing janet_table_to_struct
    JanetStruct newStruct = janet_table_to_struct(table);

    // Fuzzing janet_struct_end
    size_t num_pairs = Size / sizeof(JanetKV);
    JanetKV *kvs = janet_struct_begin(num_pairs);
    for (size_t i = 0; i < num_pairs; i++) {
        kvs[i].key.u64 = Data[i];
        kvs[i].value.u64 = Data[i];
    }
    janet_struct_end(kvs);

    // Cleanup
    janet_table_deinit(table);
    janet_table_deinit(newTable);

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}