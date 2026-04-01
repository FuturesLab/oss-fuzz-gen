extern "C" {
    #include <stdint.h>
    #include <stdlib.h>
    #include "/src/libplist/libcnary/include/node.h"
    #include "/src/libplist/include/plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Initialize plist_t object
    plist_t plist = plist_new_data((const char *)data, (uint32_t)size);

    // Initialize output parameters
    char *data_val = NULL;
    uint64_t size_val = 0;

    // Call the function-under-test
    plist_get_data_val(plist, &data_val, &size_val);

    // Clean up
    if (data_val != NULL) {
        free(data_val);
    }
    plist_free(plist);

    return 0;
}