#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

// Ensure that Janet is initialized before using any Janet functions
__attribute__((constructor))
static void init_janet() {
    janet_init();
}

int LLVMFuzzerTestOneInput_299(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract an int32_t value
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t value from the input data
    int32_t input_value;
    memcpy(&input_value, data, sizeof(int32_t));

    // Call the function-under-test
    JanetTable *table = janet_table_weakkv(input_value);

    // Perform operations on the table to maximize fuzzing effectiveness
    if (table != NULL) {
        // Add a sample key-value pair to the table
        Janet key = janet_wrap_integer(input_value);
        Janet value = janet_wrap_string(janet_cstring("fuzz_value"));
        janet_table_put(table, key, value);

        // Retrieve the value back
        Janet retrieved_value = janet_table_get(table, key);
        
        // Optionally, perform validation or further operations
        if (janet_checktype(retrieved_value, JANET_STRING)) {
            // Perform operations on the retrieved value if needed
        }
    }

    return 0;
}