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
#include <cassert>
#include "plist/plist.h"

static void fuzz_plist_array_set_item(plist_t node, const uint8_t* Data, size_t Size) {
    if (Size < 4) return;
    uint32_t index = *reinterpret_cast<const uint32_t*>(Data) % (plist_array_get_size(node) + 1);
    plist_t new_item = plist_new_string("fuzz_item");
    plist_t old_item = plist_array_get_item(node, index);
    if (old_item) {
        plist_free(old_item);
    }
    plist_array_set_item(node, new_item, index);
    plist_free(new_item); // Free the new item after setting it in the array
}

static void fuzz_plist_array_get_item_index(plist_t node) {
    uint32_t size = plist_array_get_size(node);
    for (uint32_t i = 0; i < size; ++i) {
        plist_t item = plist_array_get_item(node, i);
        uint32_t index = plist_array_get_item_index(item);
        assert(index == i || index == UINT_MAX);
    }
}

static void fuzz_plist_array_remove_item(plist_t node, const uint8_t* Data, size_t Size) {
    if (Size < 4) return;
    uint32_t size = plist_array_get_size(node);
    if (size == 0) return;
    uint32_t index = *reinterpret_cast<const uint32_t*>(Data) % size;
    plist_array_remove_item(node, index);
}

static void fuzz_plist_array_insert_item(plist_t node, const uint8_t* Data, size_t Size) {
    if (Size < 4) return;
    uint32_t index = *reinterpret_cast<const uint32_t*>(Data) % (plist_array_get_size(node) + 1);
    plist_t new_item = plist_new_string("inserted_item");
    plist_array_insert_item(node, new_item, index);
    plist_free(new_item); // Free the new item after inserting it in the array
}

static void fuzz_plist_array_get_item(plist_t node, const uint8_t* Data, size_t Size) {
    if (Size < 4) return;
    uint32_t size = plist_array_get_size(node);
    if (size == 0) return;
    uint32_t index = *reinterpret_cast<const uint32_t*>(Data) % size;
    plist_t item = plist_array_get_item(node, index);
    if (item) {
        plist_array_get_item_index(item);
    }
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    plist_t array_node = plist_new_array();
    fuzz_plist_array_set_item(array_node, Data, Size);
    fuzz_plist_array_get_item_index(array_node);
    fuzz_plist_array_remove_item(array_node, Data, Size);
    fuzz_plist_array_insert_item(array_node, Data, Size);
    fuzz_plist_array_get_item(array_node, Data, Size);
    plist_free(array_node);
    return 0;
}