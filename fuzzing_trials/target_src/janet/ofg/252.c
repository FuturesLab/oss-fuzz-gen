#include <stdint.h>
#include <stdlib.h>
#include "janet.h" // Assuming this is the header where JanetVM is defined

int LLVMFuzzerTestOneInput_252(const uint8_t *data, size_t size) {
    // Initialize the JanetVM
    janet_init();

    // Create a new Janet environment
    JanetTable *env = janet_core_env(NULL);

    // Ensure the data is null-terminated for string operations
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    Janet result;
    janet_dostring(env, input, "fuzz_input", &result);

    // Free the allocated memory for input
    free(input);

    // Deinitialize the JanetVM
    janet_deinit();

    return 0;
}