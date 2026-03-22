extern "C" {
    #include <plist/plist.h>
    #include <stdlib.h>  // For malloc and free
    #include <string.h>  // For memcpy
}

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to contain at least one character for the key
    if (size < 1) {
        return 0;
    }

    // Create a plist dictionary
    plist_t dict = plist_new_dict();
    if (!dict) {
        return 0;
    }

    // Create a key string from the input data
    char *key = (char *)malloc(size + 1);
    if (!key) {
        plist_free(dict);
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0'; // Null-terminate the string

    // Add a dummy item to the dictionary for testing
    plist_dict_set_item(dict, "dummy_key", plist_new_string("dummy_value"));

    // Call the function-under-test
    plist_t item = plist_dict_get_item(dict, key);

    // Clean up
    plist_free(dict);
    free(key);

    return 0;
}