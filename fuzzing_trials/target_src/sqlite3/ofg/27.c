#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    sqlite3_str *str;
    char *result;

    // Initialize a new sqlite3_str object
    str = sqlite3_str_new(NULL);

    // Ensure that the data is not empty before appending
    if (size > 0) {
        // Append the input data to the sqlite3_str object
        sqlite3_str_append(str, (const char *)data, size);
    }

    // Call the function-under-test
    result = sqlite3_str_finish(str);

    // Free the result if it's not NULL
    if (result != NULL) {
        sqlite3_free(result);
    }

    return 0;
}