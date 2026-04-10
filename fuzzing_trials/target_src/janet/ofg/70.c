#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Removed 'extern "C"' as this is not valid in C, it is valid in C++ for C linkage
int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    JanetTable *table;
    JanetKV *kvs;
    Janet key, value;
    JanetStruct result;

    if (size < sizeof(JanetKV)) {
        return 0;
    }

    // Initialize the Janet environment
    janet_init();

    // Create a new table
    table = janet_table(10);

    // Allocate memory for key-value pairs
    kvs = (JanetKV *)data;

    // Populate the table with key-value pairs from the input data
    for (size_t i = 0; i < size / sizeof(JanetKV); i++) {
        key = kvs[i].key;
        value = kvs[i].value;
        janet_table_put(table, key, value);
    }

    // Call the function-under-test
    result = janet_table_to_struct(table);

    // Clean up
    janet_deinit();

    return 0;
}