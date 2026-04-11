#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Initialize Janet environment
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure the data is null-terminated for use as a string
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        janet_deinit();
        return 0;
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Create a dummy JanetRegExt array
    JanetRegExt regext[] = {
        {NULL, NULL, NULL, NULL}  // Dummy entry
    };

    // Call the function-under-test
    janet_cfuns_ext(table, cstr, regext);

    // Clean up
    free(cstr);
    janet_deinit();

    return 0;
}