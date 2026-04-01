#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    int plist_key_val_compare(plist_t plist, const char *key);
}

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's enough data for at least one key-value pair

    // Create a plist object
    plist_t plist = plist_new_dict();

    // Split the input data into keys and values
    size_t key_size = size / 2;
    size_t value_size = size - key_size;

    // Create a key string from the first half of the input data
    char *key = (char *)malloc(key_size + 1);
    if (!key) {
        plist_free(plist);
        return 0;
    }
    memcpy(key, data, key_size);
    key[key_size] = '\0'; // Null-terminate the string

    // Create a value string from the second half of the input data
    char *value = (char *)malloc(value_size + 1);
    if (!value) {
        free(key);
        plist_free(plist);
        return 0;
    }
    memcpy(value, data + key_size, value_size);
    value[value_size] = '\0'; // Null-terminate the string

    // Add a key-value pair to the plist
    plist_dict_set_item(plist, key, plist_new_string(value));

    // Call the function-under-test
    plist_key_val_compare(plist, key);

    // Clean up
    free(key);
    free(value);
    plist_free(plist);

    return 0;
}