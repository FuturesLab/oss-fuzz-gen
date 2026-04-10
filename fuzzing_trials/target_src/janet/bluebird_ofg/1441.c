#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free
#include "janet.h"

int janet_streq(Janet j, const char *str);

int LLVMFuzzerTestOneInput_1441(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a string
    if (size == 0) {
        return 0;
    }

    // Initialize Janet runtime
    janet_init();

    // Create a Janet string from the input data
    Janet j = janet_stringv((const uint8_t *)data, size);

    // Create a null-terminated C string from the input data
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        janet_deinit(); // Clean up Janet runtime before returning
        return 0;
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Ensure the Janet string and C string are valid before calling the function
    if (janet_checktype(j, JANET_STRING) && cstr != NULL) {
        // Call the function-under-test
        janet_streq(j, cstr);
    }

    // Clean up
    free(cstr);

    // Clean up Janet runtime
    janet_deinit();

    return 0;
}