#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Declare and initialize a sqlite3_str object
    sqlite3_str *strObj = sqlite3_str_new(NULL);

    // If the size of data is greater than 0, use it to append a string to strObj
    if (size > 0) {
        // Append the data to the sqlite3_str object
        sqlite3_str_appendf(strObj, "%.*s", (int)size, data);
    } else {
        // Append a default string if size is 0
        sqlite3_str_appendf(strObj, "default");
    }

    // Call the function-under-test
    int errCode = sqlite3_str_errcode(strObj);

    // Clean up
    sqlite3_str_finish(strObj);

    return 0;
}