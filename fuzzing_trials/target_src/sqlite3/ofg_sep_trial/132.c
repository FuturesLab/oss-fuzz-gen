#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Initialize a sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Append the fuzzing data to the sqlite3_str object
    sqlite3_str_appendf(str, "%.*s", (int)size, data);

    // Call the function-under-test
    int length = sqlite3_str_length(str);

    // Clean up the sqlite3_str object
    sqlite3_str_finish(str);

    // Return 0 to indicate successful execution
    return 0;
}