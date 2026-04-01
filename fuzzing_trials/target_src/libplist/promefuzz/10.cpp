// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_data at plist.c:514:9 in plist.h
// plist_set_data_val at plist.c:1618:6 in plist.h
// plist_get_data_val at plist.c:1406:6 in plist.h
// plist_data_val_compare at plist.c:1845:5 in plist.h
// plist_data_val_compare_with_size at plist.c:1862:5 in plist.h
// plist_get_data_ptr at plist.c:1416:13 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
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

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a new plist data node
    plist_t node = plist_new_data(reinterpret_cast<const char*>(Data), Size);

    // Test plist_set_data_val
    if (node) {
        plist_set_data_val(node, reinterpret_cast<const char*>(Data), Size);

        // Test plist_get_data_val
        char *retrieved_val = nullptr;
        uint64_t retrieved_length = 0;
        plist_get_data_val(node, &retrieved_val, &retrieved_length);

        if (retrieved_val) {
            // Test plist_data_val_compare
            plist_data_val_compare(node, Data, Size);

            // Test plist_data_val_compare_with_size
            plist_data_val_compare_with_size(node, Data, Size);

            // Test plist_get_data_ptr
            uint64_t ptr_length = 0;
            const char* data_ptr = plist_get_data_ptr(node, &ptr_length);

            // Free the retrieved value
            plist_mem_free(retrieved_val);
        }

        // Free the plist node
        plist_free(node);
    }

    return 0;
}