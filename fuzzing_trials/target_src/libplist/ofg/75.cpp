extern "C" {
    #include <plist/plist.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to create a valid key string
    if (size == 0) {
        return 0;
    }

    // Initialize plist_t variable
    plist_t plist = plist_new_dict();

    // Create a key string from the input data
    char *key = static_cast<char*>(malloc(size + 1));
    if (!key) {
        plist_free(plist);
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0'; // Null-terminate the key string

    // Add the key to the plist with a dummy value
    plist_dict_set_item(plist, key, plist_new_string("dummy_value"));

    // Use another part of the input data to modify the plist or create additional keys
    if (size > 1) {
        char *additional_key = static_cast<char*>(malloc(size));
        if (additional_key) {
            memcpy(additional_key, data + 1, size - 1);
            additional_key[size - 1] = '\0'; // Null-terminate the additional key string
            plist_dict_set_item(plist, additional_key, plist_new_string("another_dummy_value"));
            free(additional_key);
        }
    }

    // Call the function-under-test with varied input
    int result = plist_key_val_compare_with_size(plist, key, strlen(key));

    // Clean up
    free(key);
    plist_free(plist);

    return 0;
}