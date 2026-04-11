#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1439(const uint8_t *data, size_t size) {
    JanetTable *table;
    Janet result;

    // Initialize Janet runtime
    janet_init();

    // Create a new Janet table
    table = janet_table(10); // Arbitrary initial size

    // Ensure data is null-terminated for string operations
    uint8_t *nullTerminatedData = (uint8_t *)malloc(size + 1);
    if (nullTerminatedData == NULL) {
        janet_deinit();
        return 0;
    }
    memcpy(nullTerminatedData, data, size);
    nullTerminatedData[size] = '\0';

    // Call the function-under-test
    // Use janet_cstringv to safely create a Janet string
    Janet key = janet_cstringv((const char *)nullTerminatedData);
    result = janet_table_get(table, key);

    // Clean up
    free(nullTerminatedData);
    janet_deinit();

    return 0;
}