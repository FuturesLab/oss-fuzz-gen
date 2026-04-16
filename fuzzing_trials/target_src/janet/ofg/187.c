#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

// Function prototype for the function-under-test
JanetTable *janet_table_init_raw(JanetTable *table, int32_t capacity);

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    // Define and initialize variables
    JanetTable table;
    int32_t capacity;

    // Ensure the data size is sufficient to extract an int32_t for capacity
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract the capacity from the input data
    memcpy(&capacity, data, sizeof(int32_t));

    // Ensure capacity is within a reasonable range to avoid excessive memory allocation
    if (capacity < 0 || capacity > 10000) {
        return 0;
    }

    // Call the function-under-test
    JanetTable *result = janet_table_init_raw(&table, capacity);

    // Optionally perform some checks or operations on the result
    if (result != NULL) {
        // Example: Access some fields to ensure the table was initialized
        int32_t count = result->count;
        int32_t cap = result->capacity;
        
        // Use the variables to avoid unused variable warnings
        (void)count;
        (void)cap;

        // Additional operations to ensure the table is used
        // Insert multiple dummy data to exercise the table functionality
        for (int i = 0; i < capacity && i < (size - sizeof(int32_t)) / 2; i++) {
            Janet key = janet_wrap_integer(i);
            Janet value = janet_wrap_integer(data[sizeof(int32_t) + i]);
            janet_table_put(result, key, value);
            
            // Retrieve the value to ensure it was stored correctly
            Janet retrieved = janet_table_get(result, key);
            if (janet_unwrap_integer(retrieved) != data[sizeof(int32_t) + i]) {
                abort(); // Abort if the retrieved value is not as expected
            }
        }
    }

    return 0;
}