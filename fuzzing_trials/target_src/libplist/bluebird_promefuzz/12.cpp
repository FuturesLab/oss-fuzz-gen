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
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) {
        return 0; // Not enough data to extract a uint64_t
    }

    // Extract a uint64_t value from the input data
    uint64_t val;
    memcpy(&val, Data, sizeof(uint64_t));

    // Test plist_new_uid
    plist_t uid_node = plist_new_uid(val);

    // Test plist_get_uid_val
    uint64_t retrieved_val = 0;
    plist_get_uid_val(uid_node, &retrieved_val);

    // Test plist_set_uid_val
    plist_set_uid_val(uid_node, val + 1);

    // Test plist_uid_val_compare
    int compare_result = plist_uid_val_compare(uid_node, val);

    // Test plist_new_uint
    plist_t uint_node = plist_new_uint(val);

    // Test plist_set_uint_val
    plist_set_uint_val(uint_node, val + 2);

    // Clean up
    plist_free(uid_node);
    plist_free(uint_node);

    return 0;
}