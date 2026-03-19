// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_dict at plist.c:436:9 in plist.h
// plist_new_string at plist.c:460:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_dict_set_item at plist.c:941:6 in plist.h
// plist_get_node_type at plist.c:1301:12 in plist.h
// plist_key_val_compare at plist.c:1818:5 in plist.h
// plist_key_val_contains at plist.c:1836:5 in plist.h
// plist_get_key_val at plist.c:1312:6 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_set_key_val at plist.c:1578:6 in plist.h
// plist_key_val_compare_with_size at plist.c:1827:5 in plist.h
// plist_free at plist.c:553:6 in plist.h
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
#include "plist.h"

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
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