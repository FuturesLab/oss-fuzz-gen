#include <cstdint>
#include <cstring>
#include <plist/plist.h>

extern "C" {
    uint64_t plist_dict_get_uint(plist_t, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) return 0;

    // Create a plist dictionary
    plist_t dict = plist_new_dict();

    // Use part of the data as a key
    size_t key_length = size / 2;
    char *key = new char[key_length + 1];
    memcpy(key, data, key_length);
    key[key_length] = '\0';

    // Use the rest of the data as a value
    uint64_t value = 0;
    memcpy(&value, data + key_length, sizeof(uint64_t) < (size - key_length) ? sizeof(uint64_t) : (size - key_length));

    // Insert the key-value pair into the dictionary
    plist_dict_set_item(dict, key, plist_new_uint(value));

    // Call the function-under-test
    uint64_t result = plist_dict_get_uint(dict, key);

    // Clean up
    plist_free(dict);
    delete[] key;

    return 0;
}