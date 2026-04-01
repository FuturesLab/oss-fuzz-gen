#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to create a valid string
    if (size < 2) {
        return 0;
    }

    // Create a plist dictionary
    plist_t dict = plist_new_dict();

    // Use the first part of data as the key
    size_t key_len = size / 2;
    char *key = (char *)malloc(key_len + 1);
    if (key == NULL) {
        plist_free(dict);
        return 0;
    }
    memcpy(key, data, key_len);
    key[key_len] = '\0';

    // Use the second part of data to create a plist value
    size_t value_data_len = size - key_len;
    plist_t value = plist_new_data((const char *)(data + key_len), value_data_len);

    // Call the function-under-test
    plist_dict_set_item(dict, key, value);

    // Clean up
    free(key);
    plist_free(dict);

    return 0;
}