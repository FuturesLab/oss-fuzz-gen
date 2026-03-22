#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int plist_data_val_contains(plist_t plist, const uint8_t *data, size_t size);

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to create a plist node
    if (size < 1) {
        return 0;
    }

    // Create a plist node of type PLIST_DATA
    plist_t plist = plist_new_data(reinterpret_cast<const char*>(data), size);

    // Ensure the data pointer is not NULL
    const uint8_t *data_ptr = data;
    size_t data_size = size;

    // Call the function-under-test
    int result = plist_data_val_contains(plist, data_ptr, data_size);

    // Free the plist node
    plist_free(plist);

    return 0;
}