#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1494(const uint8_t *data, size_t size) {
    // Initialize the Janet runtime
    janet_init();

    // Ensure the data is null-terminated to be a valid C string
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        janet_deinit();
        return 0; // Allocation failed, exit early
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    JanetString result = janet_cstring(cstr);

    // Clean up
    free(cstr);

    // Deinitialize the Janet runtime
    janet_deinit();

    return 0;
}