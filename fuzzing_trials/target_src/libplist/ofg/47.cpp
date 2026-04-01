#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for testing
    if (size < 2) {
        return 0;
    }

    // Create a plist dictionary
    plist_t dict = plist_new_dict();
    if (!dict) {
        return 0;
    }

    // Extract a key from the data
    size_t key_length = size - 1;
    char *key = (char *)malloc(key_length + 1);
    if (!key) {
        plist_free(dict);
        return 0;
    }
    memcpy(key, data, key_length);
    key[key_length] = '\0';

    // Add a boolean value to the dictionary with the extracted key
    plist_dict_set_item(dict, key, plist_new_bool(1));

    // Call the function-under-test
    uint8_t result = plist_dict_get_bool(dict, key);

    // Clean up
    free(key);
    plist_free(dict);

    return 0;
}