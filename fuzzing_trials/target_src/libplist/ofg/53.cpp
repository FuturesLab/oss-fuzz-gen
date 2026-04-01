#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Check if the input data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Initialize plist_t and plist_dict_iter
    plist_t plist = plist_new_dict();
    plist_dict_iter iter = NULL;
    plist_dict_new_iter(plist, &iter);

    // Initialize key and item
    char *key = NULL;
    plist_t item = NULL;

    // Add some entries to the dictionary for fuzzing
    plist_dict_set_item(plist, "key1", plist_new_string("value1"));
    plist_dict_set_item(plist, "key2", plist_new_string("value2"));
    plist_dict_set_item(plist, "key3", plist_new_string("value3"));

    // Use the input data to modify the plist in a meaningful way
    char *input_key = (char *)malloc(size + 1);
    memcpy(input_key, data, size);
    input_key[size] = '\0'; // Ensure null-termination

    plist_dict_set_item(plist, input_key, plist_new_string("fuzz_value"));

    // Call the function-under-test
    plist_dict_next_item(plist, iter, &key, &item);

    // Clean up
    if (key) {
        free(key);
    }
    if (item) {
        plist_free(item);
    }
    plist_free(plist);
    free(iter);
    free(input_key);

    return 0;
}