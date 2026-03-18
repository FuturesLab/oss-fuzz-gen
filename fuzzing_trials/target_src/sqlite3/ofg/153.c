#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Initialize a sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Ensure that the data is not NULL and has a size greater than 0
    if (data != NULL && size > 0) {
        // Append the data to the sqlite3_str object
        sqlite3_str_append(str, (const char *)data, size);
    }

    // Call the function under test
    int errcode = sqlite3_str_errcode(str);

    // Clean up the sqlite3_str object
    sqlite3_str_finish(str);

    return 0;
}