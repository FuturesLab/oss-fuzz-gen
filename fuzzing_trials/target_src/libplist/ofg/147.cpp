#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Ensure there's enough data to proceed
    if (size < 1) {
        return 0;
    }

    // Create a plist object
    plist_t plist = plist_new_dict();

    // Create a key string from the input data
    char *key = (char *)malloc(size + 1);
    if (key == NULL) {
        plist_free(plist);
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    plist_dict_get_item_key(plist, &key);

    // Clean up
    free(key);
    plist_free(plist);

    return 0;
}