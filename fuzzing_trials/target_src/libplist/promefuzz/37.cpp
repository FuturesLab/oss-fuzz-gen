// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_date at plist.c:526:9 in plist.h
// plist_set_unix_date_val at plist.c:1629:6 in plist.h
// plist_get_unix_date_val at plist.c:1448:6 in plist.h
// plist_unix_date_val_compare at plist.c:1773:5 in plist.h
// plist_date_val_compare at plist.c:1749:5 in plist.h
// plist_new_unix_date at plist.c:535:9 in plist.h
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
#include <iostream>
#include "plist.h"

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2 + sizeof(int64_t)) {
        return 0;
    }

    // Extract values from the input data
    int32_t sec = *reinterpret_cast<const int32_t*>(Data);
    int32_t usec = *reinterpret_cast<const int32_t*>(Data + sizeof(int32_t));
    int64_t unix_sec = *reinterpret_cast<const int64_t*>(Data + sizeof(int32_t) * 2);

    // Test plist_new_date
    plist_t date_node = plist_new_date(sec, usec);

    // Test plist_set_unix_date_val
    plist_set_unix_date_val(date_node, unix_sec);

    // Test plist_get_unix_date_val
    int64_t retrieved_unix_sec = 0;
    plist_get_unix_date_val(date_node, &retrieved_unix_sec);

    // Test plist_unix_date_val_compare
    int compare_result = plist_unix_date_val_compare(date_node, unix_sec);

    // Test plist_date_val_compare
    int deprecated_compare_result = plist_date_val_compare(date_node, sec, usec);

    // Test plist_new_unix_date
    plist_t unix_date_node = plist_new_unix_date(unix_sec);

    // Clean up
    plist_free(date_node);
    plist_free(unix_date_node);

    return 0;
}