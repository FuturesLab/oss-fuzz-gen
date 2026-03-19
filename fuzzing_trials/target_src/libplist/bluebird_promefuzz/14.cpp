#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure the data is null-terminated for string operations
    std::vector<char> nullTerminatedData(Data, Data + Size);
    nullTerminatedData.push_back('\0');

    // Create a plist node
    plist_t node = plist_new_dict();
    if (!node) return 0;

    // Create a key node and set a value
    plist_t keynode = plist_new_string(nullTerminatedData.data());
    if (!keynode) {
        plist_free(node);
        return 0;
    }

    // Add keynode to the dictionary
    plist_dict_set_item(node, "key", keynode);

    // 1. Test plist_get_node_type
    plist_type type = plist_get_node_type(keynode);

    // 2. Test plist_key_val_compare
    int compare_result = plist_key_val_compare(keynode, nullTerminatedData.data());

    // 3. Test plist_key_val_contains
    int contains_result = plist_key_val_contains(keynode, nullTerminatedData.data());

    // 4. Test plist_get_key_val
    char *val = nullptr;
    plist_get_key_val(keynode, &val);
    if (val) {
        plist_mem_free(val);
    }

    // 5. Test plist_set_key_val
    plist_set_key_val(keynode, nullTerminatedData.data());

    // 6. Test plist_key_val_compare_with_size
    size_t cmp_size = Size > 1 ? Data[1] : 0; // Use another byte for size
    int compare_with_size_result = plist_key_val_compare_with_size(keynode, nullTerminatedData.data(), cmp_size);

    // Clean up
    plist_free(node);

    return 0;
}