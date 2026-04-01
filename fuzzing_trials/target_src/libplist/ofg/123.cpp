#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there is at least some data

    // Create a plist from the input data
    plist_t plist = plist_new_data(reinterpret_cast<const char *>(data), size);
    if (!plist) return 0; // If plist creation fails, exit

    // Allocate memory for the key value
    char *key_val = (char *)malloc(256); // Allocate memory for key_val
    if (!key_val) {
        plist_free(plist);
        return 0; // If allocation fails, exit
    }
    memset(key_val, 0, 256); // Initialize the allocated memory

    // Call the function-under-test
    plist_get_key_val(plist, &key_val);

    // Free allocated resources
    free(key_val);
    plist_free(plist);

    return 0;
}