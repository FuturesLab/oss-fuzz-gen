// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_uid at plist.c:496:9 in plist.h
// plist_get_uid_val at plist.c:1382:6 in plist.h
// plist_set_uid_val at plist.c:1608:6 in plist.h
// plist_uid_val_compare at plist.c:1696:5 in plist.h
// plist_new_uint at plist.c:478:9 in plist.h
// plist_set_uint_val at plist.c:1598:6 in plist.h
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
#include <cstdlib>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) {
        return 0;
    }

    uint64_t val1 = *reinterpret_cast<const uint64_t*>(Data);
    const uint8_t* remainingData = Data + sizeof(uint64_t);
    size_t remainingSize = Size - sizeof(uint64_t);

    // Test plist_new_uid and plist_get_uid_val
    plist_t uid_node = plist_new_uid(val1);
    uint64_t retrieved_val = 0;
    plist_get_uid_val(uid_node, &retrieved_val);

    // Test plist_set_uid_val
    if (remainingSize >= sizeof(uint64_t)) {
        uint64_t val2 = *reinterpret_cast<const uint64_t*>(remainingData);
        plist_set_uid_val(uid_node, val2);
    }

    // Test plist_uid_val_compare
    if (remainingSize >= sizeof(uint64_t) * 2) {
        uint64_t cmp_val = *reinterpret_cast<const uint64_t*>(remainingData + sizeof(uint64_t));
        int compare_result = plist_uid_val_compare(uid_node, cmp_val);
    }

    // Test plist_new_uint and plist_set_uint_val
    plist_t uint_node = plist_new_uint(val1);
    if (remainingSize >= sizeof(uint64_t)) {
        uint64_t val3 = *reinterpret_cast<const uint64_t*>(remainingData);
        plist_set_uint_val(uint_node, val3);
    }

    // Clean up
    plist_free(uid_node);
    plist_free(uint_node);

    return 0;
}