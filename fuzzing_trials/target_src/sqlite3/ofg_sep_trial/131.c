#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    sqlite3_str *str;
    int length;

    // Initialize a new sqlite3_str object
    str = sqlite3_str_new(NULL);

    // Ensure the data is not empty and add it to the sqlite3_str object
    if (size > 0) {
        sqlite3_str_appendf(str, "%.*s", (int)size, data);
    } else {
        sqlite3_str_appendf(str, "default");
    }

    // Call the function-under-test
    length = sqlite3_str_length(str);

    // Clean up
    sqlite3_str_finish(str);

    return 0;
}