#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "/src/libplist/libcnary/include/node.h"
    #include "/src/libplist/include/plist/plist.h"

    // Assume this is the function signature from the provided library
    int plist_key_val_compare(plist_t plist, const char *key);
}

extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Ensure there is enough data for a non-empty string
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
    key[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int result = plist_key_val_compare(plist, key);

    // Clean up
    free(key);
    plist_free(plist);

    return 0;
}