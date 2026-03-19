// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_bool at plist.c:469:9 in plist.h
// plist_set_bool_val at plist.c:1593:6 in plist.h
// plist_bool_val_is_true at plist.c:1635:5 in plist.h
// plist_get_bool_val at plist.c:1353:6 in plist.h
// plist_new_dict at plist.c:436:9 in plist.h
// plist_new_dict at plist.c:436:9 in plist.h
// plist_new_bool at plist.c:469:9 in plist.h
// plist_dict_set_item at plist.c:941:6 in plist.h
// plist_dict_copy_bool at plist.c:1171:13 in plist.h
// plist_dict_get_bool at plist.c:1032:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_free at plist.c:553:6 in plist.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new boolean plist node
    uint8_t bool_val = Data[0] % 2; // Ensures 0 or 1
    plist_t bool_node = plist_new_bool(bool_val);

    // Set the boolean value on the node
    plist_set_bool_val(bool_node, bool_val);

    // Check if the boolean value is true
    int is_true = plist_bool_val_is_true(bool_node);

    // Retrieve the boolean value from the node
    uint8_t retrieved_val;
    plist_get_bool_val(bool_node, &retrieved_val);

    // Create source and target dictionaries
    plist_t source_dict = plist_new_dict();
    plist_t target_dict = plist_new_dict();

    // Use a key from the input data, if possible
    const char *key = "default_key";
    if (Size > 1) {
        size_t key_len = std::min(static_cast<size_t>(255), Size - 1); // Limit key length
        char *dynamic_key = static_cast<char*>(malloc(key_len + 1));
        if (dynamic_key) {
            memcpy(dynamic_key, Data + 1, key_len);
            dynamic_key[key_len] = '\0';
            key = dynamic_key;
        }
    }
    plist_dict_set_item(source_dict, key, plist_new_bool(bool_val));

    // Copy boolean value from source to target dictionary
    plist_err_t copy_result = plist_dict_copy_bool(target_dict, source_dict, key, nullptr);

    // Retrieve boolean value from target dictionary
    uint8_t dict_bool_val = plist_dict_get_bool(target_dict, key);

    // Cleanup
    if (key != "default_key") {
        free((void*)key);
    }
    plist_free(bool_node);
    plist_free(source_dict);
    plist_free(target_dict);

    return 0;
}