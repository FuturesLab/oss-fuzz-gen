#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Initialize plist
    plist_t plist = plist_new_dict();
    if (!plist) return 0; // Ensure plist is not NULL

    // Create a key-value pair in plist
    plist_dict_set_item(plist, "fuzz_key", plist_new_data((const char*)data, size));

    // Prepare output variables
    char *bin_data = NULL;
    uint32_t bin_size = 0;

    // Call the function-under-test
    plist_err_t result = plist_to_bin(plist, &bin_data, &bin_size);

    // Clean up
    if (bin_data) {
        free(bin_data);
    }
    plist_free(plist);

    return 0;
}