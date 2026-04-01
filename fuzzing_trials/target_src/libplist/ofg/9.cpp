extern "C" {
#include <plist/plist.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for splitting into key and value
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts: key and value
    size_t key_len = size / 2;
    size_t value_len = size - key_len;

    // Create a null-terminated string for the key
    char *key = static_cast<char *>(malloc(key_len + 1));
    if (key == nullptr) {
        return 0;
    }
    memcpy(key, data, key_len);
    key[key_len] = '\0';

    // Create a plist_t for the value
    plist_t value = plist_new_data((const char *)(data + key_len), value_len);

    // Create a plist dictionary
    plist_t dict = plist_new_dict();

    // Call the function-under-test
    plist_dict_set_item(dict, key, value);

    // Clean up
    free(key);
    plist_free(dict);

    return 0;
}