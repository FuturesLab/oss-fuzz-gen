extern "C" {
#include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Call the function-under-test
    plist_t dict = plist_new_dict();

    // Check if the dictionary is created successfully
    if (dict != NULL) {
        // Optionally, perform additional operations on the dictionary
        // For example, adding a key-value pair to the dictionary
        plist_dict_set_item(dict, "key", plist_new_string("value"));

        // Free the dictionary to avoid memory leaks
        plist_free(dict);
    }

    return 0;
}