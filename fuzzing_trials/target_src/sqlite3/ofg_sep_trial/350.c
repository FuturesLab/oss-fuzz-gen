#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_350(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated for use as a C string
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        return 0; // If memory allocation fails, exit early
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Create a new sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Call the function-under-test
    sqlite3_str_appendall(str, cstr);

    // Clean up
    sqlite3_str_finish(str);
    free(cstr);

    return 0;
}