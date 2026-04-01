extern "C" {
    #include "plist/plist.h"
    #include <stdlib.h>
    #include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a meaningful test
    if (size < 3) { // Increase minimum size to ensure both key and value can be created
        return 0;
    }

    // Create a plist node
    plist_t plist = plist_new_dict();

    // Use the first byte of data as a key length
    size_t key_length = data[0] % (size - 1); // Ensure key_length is within bounds

    // Create a key from the data
    char *key = (char *)malloc(key_length + 1);
    if (key == NULL) {
        plist_free(plist);
        return 0;
    }
    memcpy(key, data + 1, key_length);
    key[key_length] = '\0';

    // Use the remaining data as the value
    const char *value = (const char *)(data + 1 + key_length);
    size_t value_size = size - 1 - key_length;

    // Ensure value is null-terminated
    char *value_str = (char *)malloc(value_size + 1);
    if (value_str == NULL) {
        free(key);
        plist_free(plist);
        return 0;
    }
    memcpy(value_str, value, value_size);
    value_str[value_size] = '\0';

    // Add the key-value pair to the plist
    plist_dict_set_item(plist, key, plist_new_string(value_str));

    // Call the function under test
    plist_key_val_compare_with_size(plist, key, value_size);

    // Clean up
    free(key);
    free(value_str);
    plist_free(plist);

    return 0;
}