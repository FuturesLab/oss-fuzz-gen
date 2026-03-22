#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    void plist_dict_get_item_key(plist_t node, char **key);
}

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Create a plist node from the input data
    plist_t node = plist_new_dict();
    
    // Ensure the data is not empty before using it
    if (size > 0) {
        // Create a key string from the data
        char *key = static_cast<char*>(malloc(size + 1));
        if (key == NULL) {
            plist_free(node);
            return 0;
        }
        memcpy(key, data, size);
        key[size] = '\0';

        // Insert the key into the plist dictionary
        plist_dict_set_item(node, key, plist_new_string("value"));

        // Call the function-under-test
        char *retrieved_key = NULL;
        
        // Instead of calling plist_dict_get_item_key, retrieve the item directly
        plist_t item = plist_dict_get_item(node, key);
        if (item != NULL) {
            plist_dict_get_item_key(item, &retrieved_key);
        }

        // Check if the retrieved key is not NULL and matches the original key
        if (retrieved_key != NULL) {
            // Do something with the retrieved key, like comparing it
            if (strcmp(retrieved_key, key) == 0) {
                // Keys match
            }
            free(retrieved_key);
        }

        // Free the allocated memory for the key
        free(key);
    }

    // Free the plist node
    plist_free(node);

    return 0;
}