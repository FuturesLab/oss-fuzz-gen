#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) {
        return 0;
    }

    // Initialize a sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Use part of the data as the string to append
    const char *append_str = (const char *)data;
    int append_len = size > 100 ? 100 : (int)size; // Limit the length to prevent excessive usage

    // Call the function-under-test
    sqlite3_str_append(str, append_str, append_len);

    // Clean up
    sqlite3_str_finish(str);

    return 0;
}