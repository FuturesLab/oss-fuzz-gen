#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
void hts_free(void *ptr);

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for meaningful testing
    if (size < 1) {
        return 0; // Exit if input size is too small
    }

    // Allocate memory and ensure it's not NULL
    void *ptr = malloc(size + 1);
    if (ptr == NULL) {
        return 0; // Exit if allocation fails
    }

    // Copy data into allocated memory
    memcpy(ptr, data, size);

    // Null-terminate the data to ensure it's a valid string if needed
    ((char *)ptr)[size] = '\0';

    // Call the function-under-test with the allocated memory
    hts_free(ptr);

    // Additional logic can be added here to simulate more realistic usage
    // scenarios of the hts_free function, if applicable.

    return 0;
}