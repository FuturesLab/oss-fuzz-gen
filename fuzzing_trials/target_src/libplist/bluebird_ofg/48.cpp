#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Initialize plist_t variables
    plist_t source_dict = plist_new_dict();
    plist_t dest_dict = plist_new_dict();

    // Ensure the data is null-terminated for string operations
    char *key = (char *)malloc(size + 1);
    char *dest_key = (char *)malloc(size + 1);
    if (!key || !dest_key) {
        plist_free(source_dict);
        plist_free(dest_dict);
        free(key);
        free(dest_key);
        return 0;
    }

    memcpy(key, data, size);
    key[size] = '\0'; // Null-terminate the key
    memcpy(dest_key, data, size);
    dest_key[size] = '\0'; // Null-terminate the dest_key

    // Add a sample integer to the source dictionary
    plist_dict_set_item(source_dict, key, plist_new_uint(42));

    // Call the function-under-test
    plist_err_t result = plist_dict_copy_int(source_dict, dest_dict, key, dest_key);

    // Cleanup
    plist_free(source_dict);
    plist_free(dest_dict);
    free(key);
    free(dest_key);

    return 0;
}