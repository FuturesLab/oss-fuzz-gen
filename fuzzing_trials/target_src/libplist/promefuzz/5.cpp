// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_date at plist.c:526:9 in plist.h
// plist_get_date_val at plist.c:1428:6 in plist.h
// plist_unix_date_val_compare at plist.c:1773:5 in plist.h
// plist_date_val_compare at plist.c:1749:5 in plist.h
// plist_set_date_val at plist.c:1623:6 in plist.h
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

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) {
        return 0;
    }

    int32_t sec = *reinterpret_cast<const int32_t*>(Data);
    int32_t usec = *reinterpret_cast<const int32_t*>(Data + sizeof(int32_t));

    // Test plist_new_date
    plist_t date_node = plist_new_date(sec, usec);

    if (date_node) {
        // Test plist_get_date_val
        int32_t retrieved_sec = 0;
        int32_t retrieved_usec = 0;
        plist_get_date_val(date_node, &retrieved_sec, &retrieved_usec);

        // Test plist_unix_date_val_compare
        int64_t cmpval = static_cast<int64_t>(sec) + (usec / 1000000.0);
        plist_unix_date_val_compare(date_node, cmpval);

        // Test plist_date_val_compare
        plist_date_val_compare(date_node, sec, usec);

        // Test plist_set_date_val
        plist_set_date_val(date_node, sec, usec);

        // Clean up
        plist_free(date_node);
    }

    return 0;
}