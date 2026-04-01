// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_array at plist.c:443:9 in plist.h
// plist_new_string at plist.c:460:9 in plist.h
// plist_array_append_item at plist.c:742:6 in plist.h
// plist_array_get_size at plist.c:657:10 in plist.h
// plist_array_get_item at plist.c:667:9 in plist.h
// plist_array_get_item_index at plist.c:682:10 in plist.h
// plist_array_remove_item at plist.c:774:6 in plist.h
// plist_new_string at plist.c:460:9 in plist.h
// plist_array_insert_item at plist.c:758:6 in plist.h
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
#include <climits>
#include <plist/plist.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    FuzzedDataProvider dataProvider(Data, Size);

    // Create a PLIST_ARRAY node
    plist_t arrayNode = plist_new_array();

    // Randomly decide how many items to append
    int numItems = dataProvider.ConsumeIntegralInRange<int>(0, 100);
    for (int i = 0; i < numItems; ++i) {
        plist_t itemNode = plist_new_string(dataProvider.ConsumeRandomLengthString(100).c_str());
        plist_array_append_item(arrayNode, itemNode);
    }

    // Test plist_array_get_size
    uint32_t arraySize = plist_array_get_size(arrayNode);

    // Test plist_array_get_item and plist_array_get_item_index
    for (uint32_t i = 0; i < arraySize; ++i) {
        plist_t item = plist_array_get_item(arrayNode, i);
        if (item) {
            uint32_t index = plist_array_get_item_index(item);
            if (index != UINT_MAX) {
                // Test plist_array_remove_item
                plist_array_remove_item(arrayNode, index);
            }
        }
    }

    // Insert an item at a random position
    if (arraySize > 0) {
        uint32_t insertPos = dataProvider.ConsumeIntegralInRange<uint32_t>(0, arraySize - 1);
        plist_t newItem = plist_new_string(dataProvider.ConsumeRandomLengthString(100).c_str());
        plist_array_insert_item(arrayNode, newItem, insertPos);
    }

    // Clean up
    plist_free(arrayNode);

    return 0;
}