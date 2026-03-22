#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    plist_t root = NULL;

    // Create a plist from the input data
    plist_from_bin((const char*)data, size, &root);

    // Check if the root is a dictionary and has items
    if (root && plist_get_node_type(root) == PLIST_DICT) {
        plist_dict_iter iter = NULL;
        plist_dict_new_iter(root, &iter);

        if (iter != NULL) {
            char *key = NULL;
            plist_t item = NULL;
            plist_dict_next_item(root, iter, &key, &item);

            if (item != NULL) {
                // Call the function-under-test
                plist_t key_node = plist_dict_item_get_key(item);

                // Free the key if it was allocated
                if (key_node != NULL) {
                    plist_free(key_node);
                }
            }
            if (key != NULL) {
                free(key);
            }
            free(iter);
        }
    }

    // Free the plist
    if (root != NULL) {
        plist_free(root);
    }

    return 0;
}