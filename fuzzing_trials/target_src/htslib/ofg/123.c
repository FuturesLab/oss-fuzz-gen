#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern int hisremote(const char *);

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and create a string from the input data
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    int result = hisremote(input);

    // Free the allocated memory
    free(input);

    return 0;
}