#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid passing a NULL pointer
    if (size == 0) return 0;

    // Allocate memory for the binary data
    char *bin_data = (char *)malloc(size);
    if (bin_data == NULL) return 0; // Check for memory allocation failure

    // Copy the input data to the allocated memory
    memcpy(bin_data, data, size);

    // Initialize a plist_t object
    plist_t plist = NULL;

    // Call the function-under-test
    plist_err_t result = plist_from_bin(bin_data, (uint32_t)size, &plist);

    // Free allocated resources
    if (plist != NULL) {
        plist_free(plist);
    }
    free(bin_data);

    return 0;
}