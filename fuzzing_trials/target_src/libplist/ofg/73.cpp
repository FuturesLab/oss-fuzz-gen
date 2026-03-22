#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Initialize plist_t and int64_t variables
    plist_t plist = plist_new_dict();
    int64_t int_val = 0;

    // Ensure the data can be used to set an int64_t value
    if (size >= sizeof(int64_t)) {
        // Copy data into int_val
        int_val = *(reinterpret_cast<const int64_t*>(data));
    }

    // Call the function-under-test
    plist_set_int_val(plist, int_val);

    // Clean up plist
    plist_free(plist);

    return 0;
}