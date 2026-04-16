#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_352(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a Janet environment
    JanetTable *env = janet_table(0);

    // Ensure the data is null-terminated
    uint8_t *null_terminated_data = (uint8_t *)malloc(size + 1);
    if (!null_terminated_data) {
        janet_deinit();
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create a Janet object from the data
    Janet source = janet_wrap_string(janet_string(null_terminated_data, size));

    // Call the function-under-test
    JanetCompileResult result = janet_compile(source, env, null_terminated_data);

    // Clean up
    free(null_terminated_data);
    janet_deinit();

    return 0;
}