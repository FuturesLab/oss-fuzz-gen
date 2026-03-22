extern "C" {
    #include <plist/plist.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    plist_t plist = nullptr;
    char *key_val = nullptr;

    // Create a plist from the input data
    plist_from_bin((const char*)data, size, &plist);

    // Call the function-under-test
    plist_get_key_val(plist, &key_val);

    // Clean up
    if (key_val) {
        free(key_val);
    }
    if (plist) {
        plist_free(plist);
    }

    return 0;
}