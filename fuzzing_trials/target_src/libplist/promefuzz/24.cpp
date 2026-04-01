// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_from_bin at bplist.c:847:13 in plist.h
// plist_dict_get_size at plist.c:833:10 in plist.h
// plist_access_path at plist.c:1245:9 in plist.h
// plist_array_get_item at plist.c:667:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_from_openstep at oplist.c:926:13 in plist.h
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
#include <cstdarg>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a plist_t object from binary data
    plist_t plist = nullptr;
    plist_err_t err = plist_from_bin(reinterpret_cast<const char*>(Data), Size, &plist);
    if (err != PLIST_ERR_SUCCESS) {
        return 0;
    }

    // Test plist_dict_get_size
    uint32_t dict_size = plist_dict_get_size(plist);

    // Test plist_access_path with a dummy path
    if (dict_size > 0) {
        plist_t accessed_node = plist_access_path(plist, 1, "dummy_key");
    }

    // Test plist_array_get_item
    if (dict_size > 0) {
        plist_t item = plist_array_get_item(plist, 0);
    }

    // Clean up
    plist_free(plist);

    // Prepare a plist_t object from OpenStep data
    plist_t openstep_plist = nullptr;
    err = plist_from_openstep(reinterpret_cast<const char*>(Data), Size, &openstep_plist);
    if (err == PLIST_ERR_SUCCESS) {
        plist_free(openstep_plist);
    }

    return 0;
}