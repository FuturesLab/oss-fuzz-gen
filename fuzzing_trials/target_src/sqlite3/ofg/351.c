#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    // Initialize the sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    // Ensure the data is null-terminated before passing it as a string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    sqlite3_str_appendall(str, inputString);

    // Clean up
    free(inputString);
    sqlite3_str_finish(str);

    return 0;
}