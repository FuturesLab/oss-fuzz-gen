#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Declare the fuzzer function correctly for C
int LLVMFuzzerTestOneInput_372(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure the size is sufficient to extract an int32_t
    if (size < sizeof(int32_t)) {
        janet_deinit();
        return 0;
    }

    // Extract an int32_t from the input data
    int32_t capacity = *((int32_t *)data);

    // Ensure the capacity is non-negative and reasonable
    if (capacity < 0 || capacity > 1000) { // Arbitrary upper limit for safety
        janet_deinit();
        return 0;
    }

    // Initialize a JanetTable with a valid capacity
    JanetTable *table = janet_table(capacity);

    // Ensure the table is initialized
    if (table == NULL) {
        janet_deinit();
        return 0;
    }

    // Use the remaining data to insert into the table
    const uint8_t *remaining_data = data + sizeof(int32_t);
    size_t remaining_size = size - sizeof(int32_t);

    // Insert data into the table if there is enough remaining data
    if (remaining_size >= sizeof(int32_t)) {
        int32_t key = *((int32_t *)remaining_data);
        Janet value = janet_wrap_integer(key); // Simple example: wrap the key as a value
        janet_table_put(table, janet_wrap_integer(key), value);
    }

    // Additional logic can be added here to further utilize the table if needed

    // Clean up the table
    janet_table_deinit(table);

    // De-initialize the Janet environment
    janet_deinit();

    return 0;
}