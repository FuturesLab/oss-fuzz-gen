#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's enough data for the function parameters

    sqlite3_str *str;
    int count = data[0]; // Use the first byte of data for the count
    char c = (char)data[1]; // Use the second byte of data for the char

    // Initialize the sqlite3_str object
    str = sqlite3_str_new(NULL);

    // Call the function-under-test
    sqlite3_str_appendchar(str, count, c);

    // Clean up
    sqlite3_str_finish(str);

    return 0;
}