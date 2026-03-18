#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    sqlite3_str *pStr;
    char *result;

    // Initialize an sqlite3_str object
    pStr = sqlite3_str_new(NULL);

    // Simulate appending data to the sqlite3_str object if size is non-zero
    if (size > 0) {
        // Ensure the data is null-terminated for safe string operations
        char *nullTerminatedData = (char *)malloc(size + 1);
        if (nullTerminatedData == NULL) {
            return 0; // Exit if memory allocation fails
        }
        memcpy(nullTerminatedData, data, size);
        nullTerminatedData[size] = '\0';

        // Append the data to the sqlite3_str object
        sqlite3_str_appendf(pStr, "%s", nullTerminatedData);

        free(nullTerminatedData);
    }

    // Call the function under test
    result = sqlite3_str_finish(pStr);

    // Clean up
    if (result != NULL) {
        sqlite3_free(result);
    }

    return 0;
}