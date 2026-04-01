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
#include <cstring>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2 + sizeof(int64_t)) {
        return 0;
    }

    int32_t sec = 0;
    int32_t usec = 0;
    int64_t unix_sec = 0;

    memcpy(&sec, Data, sizeof(int32_t));
    memcpy(&usec, Data + sizeof(int32_t), sizeof(int32_t));
    memcpy(&unix_sec, Data + sizeof(int32_t) * 2, sizeof(int64_t));

    // Fuzz plist_new_date
    plist_t date_node = plist_new_date(sec, usec);

    if (date_node) {
        // Fuzz plist_get_date_val
        int32_t retrieved_sec = 0;
        int32_t retrieved_usec = 0;
        plist_get_date_val(date_node, &retrieved_sec, &retrieved_usec);

        // Fuzz plist_unix_date_val_compare
        plist_unix_date_val_compare(date_node, unix_sec);

        // Fuzz plist_date_val_compare
        plist_date_val_compare(date_node, sec, usec);

        // Fuzz plist_set_date_val
        plist_set_date_val(date_node, sec, usec);

        plist_free(date_node);
    }

    // Fuzz plist_new_unix_date
    plist_t unix_date_node = plist_new_unix_date(unix_sec);

    if (unix_date_node) {
        // Reuse the same fuzzed functions for the new node
        int32_t retrieved_sec = 0;
        int32_t retrieved_usec = 0;
        plist_get_date_val(unix_date_node, &retrieved_sec, &retrieved_usec);

        plist_unix_date_val_compare(unix_date_node, unix_sec);
        plist_date_val_compare(unix_date_node, sec, usec);
        plist_set_date_val(unix_date_node, sec, usec);

        plist_free(unix_date_node);
    }

    return 0;
}