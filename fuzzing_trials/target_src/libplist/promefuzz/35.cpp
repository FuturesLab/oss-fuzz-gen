// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_date at plist.c:526:9 in plist.h
// plist_get_unix_date_val at plist.c:1448:6 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_new_unix_date at plist.c:535:9 in plist.h
// plist_get_unix_date_val at plist.c:1448:6 in plist.h
// plist_set_unix_date_val at plist.c:1629:6 in plist.h
// plist_unix_date_val_compare at plist.c:1773:5 in plist.h
// plist_date_val_compare at plist.c:1749:5 in plist.h
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
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int64_t)) return 0;

    int64_t sec = *reinterpret_cast<const int64_t*>(Data);
    int32_t sec2001 = static_cast<int32_t>(sec % INT32_MAX);
    int32_t usec = static_cast<int32_t>((sec >> 32) % 1000000);

    // Fuzz plist_new_date (deprecated)
    plist_t date_node_2001 = plist_new_date(sec2001, usec);
    if (date_node_2001) {
        int64_t unix_sec;
        plist_get_unix_date_val(date_node_2001, &unix_sec);
        plist_free(date_node_2001);
    }

    // Fuzz plist_new_unix_date
    plist_t date_node_unix = plist_new_unix_date(sec);
    if (date_node_unix) {
        int64_t unix_sec;
        plist_get_unix_date_val(date_node_unix, &unix_sec);

        // Fuzz plist_set_unix_date_val
        plist_set_unix_date_val(date_node_unix, sec);

        // Fuzz plist_unix_date_val_compare
        int cmp_result = plist_unix_date_val_compare(date_node_unix, sec);

        // Fuzz plist_date_val_compare (deprecated)
        int cmp_result_2001 = plist_date_val_compare(date_node_unix, sec2001, usec);

        plist_free(date_node_unix);
    }

    return 0;
}