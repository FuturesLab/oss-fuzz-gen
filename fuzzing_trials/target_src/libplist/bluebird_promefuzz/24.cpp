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

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int64_t)) {
        return 0;
    }

    int64_t signed_val;
    uint64_t unsigned_val;
    memcpy(&signed_val, Data, sizeof(int64_t));
    memcpy(&unsigned_val, Data, sizeof(uint64_t));

    // Create a new plist int node
    plist_t node = plist_new_int(signed_val);

    // Retrieve and compare signed integer value
    int64_t retrieved_signed_val = 0;
    plist_get_int_val(node, &retrieved_signed_val);
    plist_int_val_compare(node, signed_val);

    // Retrieve and compare unsigned integer value
    uint64_t retrieved_unsigned_val = 0;
    plist_get_uint_val(node, &retrieved_unsigned_val);
    plist_uint_val_compare(node, unsigned_val);

    // Check if the value is negative
    plist_int_val_is_negative(node);

    // Clean up
    plist_free(node);

    return 0;
}