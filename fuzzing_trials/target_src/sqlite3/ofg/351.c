#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    // Initialize a sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Ensure the data is null-terminated for use as a C string
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        sqlite3_str_finish(str);
        return 0;
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Call the function-under-test
    sqlite3_str_appendall(str, cstr);

    // Clean up
    free(cstr);
    sqlite3_str_finish(str);

    return 0;
}