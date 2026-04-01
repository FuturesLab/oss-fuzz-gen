extern "C" {
    #include <plist/plist.h>
}

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Ensure that size is at least 1 to extract a valid string
    if (size < 1) {
        return 0;
    }

    // Create a dummy plist dictionary
    plist_t plist = plist_new_dict();

    // Add a dummy key-value pair to the dictionary
    const char *dummy_key = "dummy_key";
    plist_dict_set_item(plist, dummy_key, plist_new_string("dummy_value"));

    // Use the fuzz data as a key
    char *key = new char[size + 1];
    memcpy(key, data, size);
    key[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    plist_dict_remove_item(plist, key);

    // Clean up
    delete[] key;
    plist_free(plist);

    return 0;
}