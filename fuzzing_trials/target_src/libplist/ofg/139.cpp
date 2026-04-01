extern "C" {
#include <plist/plist.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) {
        return 0;
    }

    // Create a plist dictionary
    plist_t dict = plist_new_dict();

    // Use part of the data to create a key
    size_t key_length = size / 2;
    char *key = (char *)malloc(key_length + 1);
    if (!key) {
        plist_free(dict);
        return 0;
    }
    memcpy(key, data, key_length);
    key[key_length] = '\0';

    // Use the rest of the data as a value
    size_t value_length = size - key_length;
    char *value = (char *)malloc(value_length + 1);
    if (!value) {
        free(key);
        plist_free(dict);
        return 0;
    }
    memcpy(value, data + key_length, value_length);
    value[value_length] = '\0';

    // Add the key-value pair to the dictionary
    plist_dict_set_item(dict, key, plist_new_string(value));

    // Fuzz the function-under-test
    plist_t item = plist_dict_get_item(dict, key);

    // Clean up
    free(key);
    free(value);
    plist_free(dict);

    return 0;
}