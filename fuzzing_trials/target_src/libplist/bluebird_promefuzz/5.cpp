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
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a new plist array
    plist_t array = plist_new_array();

    // Append items to the array based on input data
    for (size_t i = 0; i < Size; ++i) {
        plist_t item = plist_new_array(); // Create a new item (empty array for simplicity)

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_new_array to plist_get_string_val

        plist_get_string_val(array, (char **)"w");

        // End mutation: Producer.APPEND_MUTATOR

        plist_array_append_item(array, item);
    }

    // Create an iterator for the array
    plist_array_iter iter = nullptr;
    plist_array_new_iter(array, &iter);

    // Iterate over the array items
    plist_t item = nullptr;
    while (true) {
        plist_array_next_item(array, iter, &item);
        if (!item) {
                break;
        }
    }

    // Get the nth item and remove it
    if (Size > 0) {
        uint32_t index = Data[0] % Size; // Ensure index is within bounds
        plist_t nth_item = plist_array_get_item(array, index);
        if (nth_item) {
            plist_array_item_remove(nth_item);
        }
    }

    // Cleanup
    free(iter);
    plist_free(array);

    return 0;
}