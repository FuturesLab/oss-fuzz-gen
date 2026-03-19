// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_string at plist.c:460:9 in plist.h
// plist_string_val_compare at plist.c:1791:5 in plist.h
// plist_string_val_contains at plist.c:1809:5 in plist.h
// plist_get_string_val at plist.c:1326:6 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_set_string_val at plist.c:1588:6 in plist.h
// plist_new_dict at plist.c:436:9 in plist.h
// plist_new_dict at plist.c:436:9 in plist.h
// plist_copy at plist.c:652:9 in plist.h
// plist_dict_set_item at plist.c:941:6 in plist.h
// plist_dict_copy_string at plist.c:1211:13 in plist.h
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
#include <cstddef>
#include <cstring>
#include "plist.h"

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Convert the input data into a C-string
    char *cstr = new char[Size + 1];
    memcpy(cstr, Data, Size);
    cstr[Size] = '\0';

    // Create a plist string node
    plist_t strnode = plist_new_string(cstr);

    // Compare the plist string node value with another string
    plist_string_val_compare(strnode, "compare_string");

    // Check if the plist string node contains a substring
    plist_string_val_contains(strnode, "substring");

    // Retrieve and free the string value from the plist node
    char *retrieved_val = nullptr;
    plist_get_string_val(strnode, &retrieved_val);
    if (retrieved_val) {
        plist_mem_free(retrieved_val);
    }

    // Set a new string value to the plist node
    plist_set_string_val(strnode, "new_value");

    // Create source and target dictionaries
    plist_t source_dict = plist_new_dict();
    plist_t target_dict = plist_new_dict();

    // Insert the string node into the source dictionary
    plist_dict_set_item(source_dict, "key", plist_copy(strnode));

    // Copy string node from source to target dictionary
    plist_dict_copy_string(target_dict, source_dict, "key", nullptr);

    // Clean up
    plist_free(strnode);
    plist_free(source_dict);
    plist_free(target_dict);
    delete[] cstr;

    return 0;
}