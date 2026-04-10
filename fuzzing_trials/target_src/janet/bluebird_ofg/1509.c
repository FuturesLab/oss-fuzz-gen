#include <stdint.h>
#include "janet.h"

// Initialize the Janet environment
__attribute__((constructor))
static void init_janet(void) {
    janet_init();
}

// Clean up the Janet environment
__attribute__((destructor))
static void deinit_janet(void) {
    janet_deinit();
}

// Fuzzing function
int LLVMFuzzerTestOneInput_1509(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) {
        return 0;
    }

    // Initialize Janet interpreter
    JanetArray *array = janet_array(2);
    JanetTable *table = janet_table(2);

    // Create two Janet values from the input data
    Janet key = janet_wrap_number((double)data[0]);
    Janet value = janet_wrap_number((double)data[1]);

    // Store the values in a Janet table
    janet_table_put(table, key, value);

    // Call the function-under-test
    Janet result = janet_get(janet_wrap_table(table), key);

    // Use the result to prevent compiler optimizations
    if (janet_checktype(result, JANET_NUMBER)) {
        double num = janet_unwrap_number(result);
        (void)num; // Do something with num if needed
    }

    // No need to manually deinitialize the array and table
    // Janet handles memory management automatically

    return 0;
}