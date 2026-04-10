#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/janet/src/include/janet.h" // Correct path for the Janet API header

int LLVMFuzzerTestOneInput_300(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for an int32_t
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t value from the input data
    int32_t capacity = *((int32_t *)data);

    // Ensure that the capacity is a positive integer and within a reasonable range
    if (capacity <= 0 || capacity > 1000) { // Assuming 1000 is a reasonable upper limit
        return 0;
    }

    // Call the function-under-test
    JanetTable *table = janet_table_weakkv(capacity);

    // Check if the table was created successfully
    if (table == NULL) {
        return 0;
    }

    // Perform additional operations on the table to utilize it
    // For example, insert a key-value pair
    Janet key = janet_wrap_integer(1);
    Janet value = janet_wrap_integer(2);
    janet_table_put(table, key, value);

    // Another example: retrieve the inserted value
    Janet retrieved_value = janet_table_get(table, key);

    // Clean up resources
    janet_table_clear(table); // Assuming janet_table_clear is the correct function to deallocate or reset the table

    // Return 0 to indicate successful execution
    return 0;
}