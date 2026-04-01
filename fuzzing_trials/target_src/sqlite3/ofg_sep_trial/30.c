#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Initialize a sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Ensure that the data is not empty
    if (size > 0) {
        // Append data to the sqlite3_str object
        sqlite3_str_append(str, (const char *)data, size);
    } else {
        // Append a non-empty string to ensure str is not NULL
        sqlite3_str_append(str, "non-empty", 9);
    }

    // Call the function-under-test
    char *result = sqlite3_str_finish(str);

    // Free the result if it's not NULL
    if (result) {
        sqlite3_free(result);
    }

    return 0;
}