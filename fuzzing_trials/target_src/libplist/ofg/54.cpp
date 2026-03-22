#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a plist from the input data
    plist_t plist = NULL;
    plist_from_bin((const char *)data, size, &plist);

    if (!plist) {
        return 0;
    }

    // Initialize a dictionary iterator
    plist_dict_iter iter = NULL;
    plist_dict_new_iter(plist, &iter);

    if (!iter) {
        plist_free(plist);
        return 0;
    }

    // Prepare variables for plist_dict_next_item
    char *key = NULL;
    plist_t value = NULL;

    // Call the function-under-test
    plist_dict_next_item(plist, iter, &key, &value);

    // Clean up
    if (key) {
        free(key);
    }
    if (value) {
        plist_free(value);
    }
    plist_free(plist);
    free(iter);

    return 0;
}