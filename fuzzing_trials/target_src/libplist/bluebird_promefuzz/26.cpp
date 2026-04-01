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

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    plist_t source_dict = plist_new_dict();
    plist_t target_dict = plist_new_dict();

    // Create keys for testing
    const char *key = "test_key";
    const char *alt_key = "alt_key";

    // Use the first byte of data to decide which type of value to insert and test
    uint8_t type = Data[0];
    Data++;
    Size--;

    switch (type % 6) {
        case 0: {
            // Test plist_dict_copy_int
            if (Size < sizeof(int64_t)) break;
            int64_t value;
            memcpy(&value, Data, sizeof(int64_t));
            plist_dict_set_item(source_dict, key, plist_new_int(value));
            plist_dict_copy_int(target_dict, source_dict, key, alt_key);
            break;
        }
        case 1: {
            // Test plist_dict_copy_uint
            if (Size < sizeof(uint64_t)) break;
            uint64_t value;
            memcpy(&value, Data, sizeof(uint64_t));
            plist_dict_set_item(source_dict, key, plist_new_uint(value));
            plist_dict_copy_uint(target_dict, source_dict, key, alt_key);
            break;
        }
        case 2: {
            // Test plist_dict_copy_string
            char *string_value = (char *)malloc(Size + 1);
            if (!string_value) break;
            memcpy(string_value, Data, Size);
            string_value[Size] = '\0';
            plist_dict_set_item(source_dict, key, plist_new_string(string_value));
            plist_dict_copy_string(target_dict, source_dict, key, alt_key);
            free(string_value);
            break;
        }
        case 3: {
            // Test plist_dict_copy_item
            plist_dict_set_item(source_dict, key, plist_new_string("sample"));
            plist_dict_copy_item(target_dict, source_dict, key, alt_key);
            break;
        }
        case 4: {
            // Test plist_dict_copy_data
            plist_dict_set_item(source_dict, key, plist_new_data((const char *)Data, Size));
            plist_dict_copy_data(target_dict, source_dict, key, alt_key);
            break;
        }
        case 5: {
            // Test plist_dict_copy_bool
            uint8_t bool_value = Data[0] % 2;
            plist_dict_set_item(source_dict, key, plist_new_bool(bool_value));
            plist_dict_copy_bool(target_dict, source_dict, key, alt_key);
            break;
        }
    }

    plist_free(source_dict);
    plist_free(target_dict);

    return 0;
}