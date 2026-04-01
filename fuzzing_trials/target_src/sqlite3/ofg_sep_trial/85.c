#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

// Fuzzing harness for sqlite3_str_value
int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Initialize a sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Ensure data is not NULL and size is greater than 0
    if (data != NULL && size > 0) {
        // Append the input data to the sqlite3_str object
        sqlite3_str_append(str, (const char *)data, (int)size);
    }

    // Call the function-under-test
    char *result = sqlite3_str_value(str);

    // Use the result in some way to prevent it from being optimized away
    if (result != NULL) {
        // Print the result length (for demonstration purposes)
        volatile size_t result_length = strlen(result);
    }

    // Free the sqlite3_str object
    sqlite3_str_finish(str);

    return 0;
}