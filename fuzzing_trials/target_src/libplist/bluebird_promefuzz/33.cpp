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

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create dummy dictionaries
    plist_t target_dict = plist_new_dict();
    plist_t source_dict = plist_new_dict();

    // Prepare keys
    const char *key = "key";
    const char *alt_key = "alt_key";

    // Add data to source dictionary
    plist_t data_node = plist_new_data(reinterpret_cast<const char*>(Data), static_cast<uint64_t>(Size));
    plist_dict_set_item(source_dict, key, plist_copy(data_node));
    plist_dict_set_item(source_dict, alt_key, plist_copy(data_node));

    // Test plist_dict_copy_item
    plist_dict_copy_item(target_dict, source_dict, key, alt_key);

    // Test plist_dict_copy_data
    plist_dict_copy_data(target_dict, source_dict, key, alt_key);

    // Test plist_dict_get_item
    plist_t item = plist_dict_get_item(source_dict, key);
    if (item) {
        // Test plist_get_data_ptr
        uint64_t length = 0;
        const char *data_ptr = plist_get_data_ptr(item, &length);

        // Test plist_get_string_ptr
        const char *string_ptr = plist_get_string_ptr(item, &length);

        // Ensure data_ptr and string_ptr are not null
        if (data_ptr && string_ptr) {
            // Compare node values
            plist_compare_node_value(item, item);
        }
    }

    // Cleanup
    plist_free(target_dict);
    plist_free(source_dict);
    plist_free(data_node);

    return 0;
}