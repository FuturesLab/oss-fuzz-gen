#include <stdint.h>
#include <stdlib.h>
#include "janet.h"

// Define the fuzzer entry point without the C++ linkage specification
int LLVMFuzzerTestOneInput_967(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0; // Ensure there's enough data for a Janet object
    }

    // Initialize Janet runtime
    janet_init();

    // Create a JanetBuffer
    JanetBuffer *buffer = janet_buffer(10);

    // Create a Janet object using the first part of the data
    Janet janet_obj = janet_wrap_number(*(const double *)data);

    // Create a JanetTable
    JanetTable *table = janet_table(0);

    // Use the remaining data as a simple integer option
    int options = 0;
    if (size > sizeof(Janet)) {
        options = (int)data[sizeof(Janet)];
    }

    // Call the function-under-test
    janet_marshal(buffer, janet_obj, table, options);

    // Clean up
    janet_deinit();

    return 0;
}