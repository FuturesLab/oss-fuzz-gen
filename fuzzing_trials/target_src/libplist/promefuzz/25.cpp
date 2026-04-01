// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_array at plist.c:443:9 in plist.h
// plist_new_array at plist.c:443:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_array_append_item at plist.c:742:6 in plist.h
// plist_array_new_iter at plist.c:805:6 in plist.h
// plist_array_next_item at plist.c:814:6 in plist.h
// plist_get_parent at plist.c:1296:9 in plist.h
// plist_array_item_remove at plist.c:790:6 in plist.h
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
#include <cstdio>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    // Create a new plist array
    plist_t array = plist_new_array();
    if (!array) return 0;

    // Create a dummy item to append
    plist_t item = plist_new_array();
    if (!item) {
        plist_free(array);
        return 0;
    }

    // Append item to array
    plist_array_append_item(array, item);

    // Create an iterator for the array
    plist_array_iter iter = nullptr;
    plist_array_new_iter(array, &iter);

    // Iterate through the array items
    plist_t current_item = nullptr;
    plist_array_next_item(array, iter, &current_item);

    // Check parent relationship
    plist_t parent = plist_get_parent(current_item);

    // Remove the item from the array
    plist_array_item_remove(current_item);

    // Clean up
    free(iter);
    plist_free(array);

    return 0;
}