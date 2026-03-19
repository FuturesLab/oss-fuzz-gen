// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_uid at plist.c:496:9 in plist.h
// plist_get_uid_val at plist.c:1382:6 in plist.h
// plist_uid_val_compare at plist.c:1696:5 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_new_uint at plist.c:478:9 in plist.h
// plist_get_uint_val at plist.c:1365:6 in plist.h
// plist_set_uint_val at plist.c:1598:6 in plist.h
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
extern "C" {
#include <plist/plist.h>
}

#include <cstdint>
#include <cstdlib>

static void fuzz_plist_new_uid(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return;
    uint64_t val;
    memcpy(&val, Data, sizeof(uint64_t));

    plist_t uid_node = plist_new_uid(val);
    if (uid_node) {
        uint64_t retrieved_val = 0;
        plist_get_uid_val(uid_node, &retrieved_val);

        int cmp_result = plist_uid_val_compare(uid_node, val);

        plist_free(uid_node);
    }
}

static void fuzz_plist_new_uint(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return;
    uint64_t val;
    memcpy(&val, Data, sizeof(uint64_t));

    plist_t uint_node = plist_new_uint(val);
    if (uint_node) {
        uint64_t retrieved_val = 0;
        plist_get_uint_val(uint_node, &retrieved_val);

        plist_set_uint_val(uint_node, val + 1);

        plist_free(uint_node);
    }
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    fuzz_plist_new_uid(Data, Size);
    fuzz_plist_new_uint(Data, Size);

    return 0;
}