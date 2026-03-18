#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Initialize a sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Ensure that the data is not empty before appending
    if (size > 0) {
        // Append the data to the sqlite3_str object
        sqlite3_str_appendf(str, "%.*s", (int)size, data);
    }

    // Call the function-under-test
    int length = sqlite3_str_length(str);

    // Clean up by freeing the sqlite3_str object
    sqlite3_str_finish(str);

    return 0;
}