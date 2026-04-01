extern "C" {
    #include <plist/plist.h>
}

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a plist dictionary
    plist_t dict = plist_new_dict();

    // Create a null-terminated string from the input data
    char *key = new char[size + 1];
    memcpy(key, data, size);
    key[size] = '\0';

    // Add a dummy item to the dictionary with the given key
    plist_dict_set_item(dict, key, plist_new_string("dummy_value"));

    // Call the function-under-test
    plist_dict_remove_item(dict, key);

    // Clean up
    plist_free(dict);
    delete[] key;

    return 0;
}