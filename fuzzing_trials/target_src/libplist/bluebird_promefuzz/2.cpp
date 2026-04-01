#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    plist_t source_dict = plist_new_dict();
    plist_t target_dict = plist_new_dict();

    // Create some keys and values for testing
    const char *key1 = "key1";
    const char *key2 = "key2";
    const char *alt_key = "alt_key";

    // Add some values to the source dictionary
    plist_dict_set_item(source_dict, key1, plist_new_uint(Size));

    // Ensure the data is null-terminated before using it as a string
    char *data_string = (char *)malloc(Size + 1);
    if (data_string) {
        memcpy(data_string, Data, Size);
        data_string[Size] = '\0';  // Null-terminate the string
        plist_dict_set_item(source_dict, key2, plist_new_string(data_string));
        free(data_string);
    }

    plist_dict_set_item(source_dict, alt_key, plist_new_bool(Data[0] % 2));

    // Fuzzing plist_dict_merge
    plist_dict_merge(&target_dict, source_dict);

    // Fuzzing plist_dict_copy_uint
    plist_dict_copy_uint(target_dict, source_dict, key1, nullptr);

    // Fuzzing plist_dict_copy_string
    plist_dict_copy_string(target_dict, source_dict, key2, nullptr);

    // Fuzzing plist_dict_copy_item
    plist_dict_copy_item(target_dict, source_dict, key1, alt_key);

    // Fuzzing plist_dict_copy_data
    plist_dict_copy_data(target_dict, source_dict, key2, nullptr);

    // Fuzzing plist_dict_copy_bool
    plist_dict_copy_bool(target_dict, source_dict, alt_key, key1);

    // Clean up
    plist_free(source_dict);
    plist_free(target_dict);

    return 0;
}