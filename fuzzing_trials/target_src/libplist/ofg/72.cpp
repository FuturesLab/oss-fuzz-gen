#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Ensure that size is at least 1 to have non-zero data length
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the data buffer and ensure it is null-terminated
    char *data_buffer = (char *)malloc(size + 1);
    if (data_buffer == NULL) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(data_buffer, data, size);
    data_buffer[size] = '\0';

    // Choose a non-zero uint64_t value for the second parameter
    uint64_t length = (uint64_t)size;

    // Call the function-under-test
    plist_t result = plist_new_data(data_buffer, length);

    // Clean up allocated memory
    free(data_buffer);

    // If a plist was created, free it
    if (result != NULL) {
        plist_free(result);
    }

    return 0;
}