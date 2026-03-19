#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create plist dictionaries
    plist_t source_dict = plist_new_dict();
    plist_t target_dict = plist_new_dict();

    // Create a key string from the input data
    char *key = static_cast<char*>(malloc(Size + 1));
    if (!key) {
        plist_free(source_dict);
        plist_free(target_dict);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Create a dummy item and insert it into the source dictionary
    plist_t item = plist_new_string("dummy_value");
    plist_dict_set_item(source_dict, key, item);

    // Test plist_dict_get_item_key
    char *retrieved_key = nullptr;
    plist_t retrieved_item = plist_dict_get_item(source_dict, key);
    if (retrieved_item) {
        plist_dict_get_item_key(retrieved_item, &retrieved_key);
        if (retrieved_key) {
            free(retrieved_key);
        }
    }

    // Test plist_dict_copy_item
    plist_dict_copy_item(target_dict, source_dict, key, nullptr);

    // Test plist_dict_get_item
    plist_t copied_item = plist_dict_get_item(target_dict, key);

    // Test plist_dict_next_item
    plist_dict_iter iter = nullptr;
    plist_dict_new_iter(source_dict, &iter);
    if (iter) {
        plist_dict_next_item(source_dict, iter, &retrieved_key, &retrieved_item);
        if (retrieved_key) {
            free(retrieved_key);
        }
        free(iter);
    }

    // Test plist_dict_set_item
    plist_t new_item = plist_new_string("new_value");
    plist_dict_set_item(target_dict, key, new_item);

    // Test plist_dict_get_bool
    uint8_t bool_value = plist_dict_get_bool(target_dict, key);

    // Cleanup
    plist_free(source_dict);
    plist_free(target_dict);
    free(key);

    return 0;
}