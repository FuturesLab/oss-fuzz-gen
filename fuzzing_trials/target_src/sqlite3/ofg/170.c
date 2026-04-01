#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Initialize variables
    sqlite3_str *str;
    int n;
    char c;

    // Create a new sqlite3_str object
    str = sqlite3_str_new(NULL);

    // Ensure size is large enough to extract required values
    if (size < 5) {
        sqlite3_str_finish(str);
        return 0;
    }

    // Extract values from the input data
    n = (int)data[0]; // Extracting an integer value
    c = (char)data[1]; // Extracting a character

    // Call the function under test
    sqlite3_str_appendchar(str, n, c);

    // Clean up
    sqlite3_str_finish(str);

    return 0;
}