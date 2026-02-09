#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    sqlite3_str *str;
    int integerParam;
    char charParam;

    // Initialize the sqlite3_str object
    str = sqlite3_str_new(0);
    if (str == NULL) {
        return 0; // Early exit if allocation fails
    }

    // Ensure size is within a reasonable range for our parameters
    if (size < 3) {
        sqlite3_str_finish(str);
        return 0; // Not enough data to proceed
    }

    // Use the first byte of the data as an integer parameter
    integerParam = (int)data[0]; // Cast to int
    // Use the second byte of the data as a character parameter
    charParam = (char)data[1];

    // Call the function under test
    sqlite3_str_appendchar(str, integerParam, charParam);

    // Cleanup
    sqlite3_str_finish(str);
    return 0;
}