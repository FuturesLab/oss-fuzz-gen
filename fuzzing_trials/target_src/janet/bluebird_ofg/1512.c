#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "janet.h"

// Forward declaration of the function-under-test
Janet janet_ev_lasterr();

int LLVMFuzzerTestOneInput_1512(const uint8_t *data, size_t size) {
    // Initialize the Janet VM
    janet_init();

    // Call the function-under-test
    Janet last_error = janet_ev_lasterr();

    // Example: Convert the Janet value to a string for inspection (if applicable)
    const char *error_str = janet_to_string(last_error);
    
    // Print or log the error string for debugging purposes
    if (error_str != NULL) {
        printf("Last error: %s\n", error_str);
    }

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}