#include <cstdint>
#include <cstddef>
#include <cstring>
#include <plist/plist.h>

// Ensure the function-under-test is properly linked
extern "C" {
    void plist_set_data_val(plist_t plist, const char *val, uint64_t length);
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Initialize plist
    plist_t plist = plist_new_dict();

    // Prepare a non-null string
    const char *val = "test_data";
    uint64_t length = 9;  // Length of the string "test_data"

    // Call the function-under-test
    plist_set_data_val(plist, val, length);

    // Clean up plist
    plist_free(plist);

    return 0;
}