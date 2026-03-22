#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Ensure there's enough data to use
    if (size < 2) {
        return 0;
    }

    // Initialize plist
    plist_t plist = plist_new_dict();

    // Create a null-terminated string from the input data
    char *key_val = (char *)malloc(size + 1);
    if (key_val == NULL) {
        plist_free(plist);
        return 0;
    }
    memcpy(key_val, data, size);
    key_val[size] = '\0';

    // Call the function-under-test
    plist_set_key_val(plist, key_val);

    // Clean up
    free(key_val);
    plist_free(plist);

    return 0;
}