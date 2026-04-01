// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_array at plist.c:443:9 in plist.h
// plist_new_string at plist.c:460:9 in plist.h
// plist_array_get_size at plist.c:657:10 in plist.h
// plist_array_get_item at plist.c:667:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_array_set_item at plist.c:714:6 in plist.h
// plist_array_get_size at plist.c:657:10 in plist.h
// plist_array_get_item at plist.c:667:9 in plist.h
// plist_array_item_remove at plist.c:790:6 in plist.h
// plist_array_get_size at plist.c:657:10 in plist.h
// plist_array_remove_item at plist.c:774:6 in plist.h
// plist_array_get_size at plist.c:657:10 in plist.h
// plist_array_insert_item at plist.c:758:6 in plist.h
// plist_array_append_item at plist.c:742:6 in plist.h
// plist_array_get_size at plist.c:657:10 in plist.h
// plist_array_get_item at plist.c:667:9 in plist.h
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
#include <cassert>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least some data

    // Create a PLIST_ARRAY node
    plist_t array_node = plist_new_array();

    // Use the first byte to determine the operation
    uint8_t operation = Data[0];
    uint32_t index = 0;
    if (Size > 4) {
        index = *(reinterpret_cast<const uint32_t*>(Data + 1)) % (Size - 1);
    }

    // Create a dummy item to be used in operations
    plist_t dummy_item = plist_new_string("dummy");

    switch (operation % 6) {
        case 0: { // plist_array_set_item
            if (index < plist_array_get_size(array_node)) {
                plist_t existing_item = plist_array_get_item(array_node, index);
                plist_free(existing_item);
                plist_array_set_item(array_node, dummy_item, index);
            }
            break;
        }
        case 1: { // plist_array_item_remove
            if (index < plist_array_get_size(array_node)) {
                plist_t item = plist_array_get_item(array_node, index);
                plist_array_item_remove(item);
            }
            break;
        }
        case 2: { // plist_array_remove_item
            if (index < plist_array_get_size(array_node)) {
                plist_array_remove_item(array_node, index);
            }
            break;
        }
        case 3: { // plist_array_insert_item
            if (index <= plist_array_get_size(array_node)) {
                plist_array_insert_item(array_node, dummy_item, index);
            }
            break;
        }
        case 4: { // plist_array_append_item
            plist_array_append_item(array_node, dummy_item);
            break;
        }
        case 5: { // plist_array_get_item
            if (index < plist_array_get_size(array_node)) {
                plist_t item = plist_array_get_item(array_node, index);
                // Do something with item if needed
            }
            break;
        }
        default:
            break;
    }

    // Cleanup
    plist_free(array_node);
    return 0;
}