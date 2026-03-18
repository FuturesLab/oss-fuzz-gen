#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_303(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;
    }

    // Copy the input data to the string and null-terminate it
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    int result = sqlite3_keyword_check(inputString, (int)size);

    // Free the allocated memory
    free(inputString);

    return 0;
}