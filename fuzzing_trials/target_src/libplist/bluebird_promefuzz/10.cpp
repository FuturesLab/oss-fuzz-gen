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

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy key from the input data
    size_t key_length = Size > 255 ? 255 : Size;
    char key[256];
    memcpy(key, Data, key_length);
    key[key_length] = '\0';

    // Initialize a dictionary plist
    plist_t dict = plist_new_dict();

    // Create an integer plist node
    int64_t initial_value = static_cast<int64_t>(Data[0]);
    plist_t int_node = plist_new_int(initial_value);

    // Set the integer node in the dictionary
    plist_dict_set_item(dict, key, int_node);

    // Test plist_dict_get_int
    int64_t retrieved_value = plist_dict_get_int(dict, key);

    // Test plist_get_int_val
    int64_t int_val = 0;
    plist_get_int_val(int_node, &int_val);

    // Test plist_set_int_val
    plist_set_int_val(int_node, retrieved_value + 1);

    // Test plist_int_val_compare
    int compare_result = plist_int_val_compare(int_node, retrieved_value);

    // Test plist_int_val_is_negative
    int is_negative = plist_int_val_is_negative(int_node);

    // Clean up
    plist_free(dict);

    return 0;
}