#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include this header for malloc and free

int LLVMFuzzerTestOneInput_350(const uint8_t *data, size_t size) {
    // Initialize the sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Ensure the input data is null-terminated
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Call the function-under-test
    sqlite3_str_appendall(str, inputData);

    // Clean up
    free(inputData);
    sqlite3_str_finish(str);

    return 0;
}