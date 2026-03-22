#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int64_t plist_dict_get_int(plist_t, const char *);

extern "C" int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for a key string
    if (size < 2) return 0;

    // Create a plist dictionary
    plist_t dict = plist_new_dict();

    // Use part of the data as a key
    size_t key_len = size / 2;  // Use half of the data as the key
    char *key = (char *)malloc(key_len + 1);
    if (!key) {
        plist_free(dict);
        return 0;
    }
    memcpy(key, data, key_len);
    key[key_len] = '\0';  // Null-terminate the key

    // Use the rest of the data as an integer value
    int64_t value = 0;
    if (size > key_len) {
        memcpy(&value, data + key_len, sizeof(int64_t));
    }

    // Insert the key-value pair into the plist dictionary
    plist_dict_set_item(dict, key, plist_new_int(value));

    // Call the function-under-test
    int64_t retrieved_value = plist_dict_get_int(dict, key);

    // Clean up
    free(key);
    plist_free(dict);

    return 0;
}