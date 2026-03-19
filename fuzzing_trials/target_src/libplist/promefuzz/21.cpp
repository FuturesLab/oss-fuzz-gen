// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_from_openstep at oplist.c:926:13 in plist.h
// plist_dict_get_size at plist.c:833:10 in plist.h
// plist_access_pathv at plist.c:1221:9 in plist.h
// plist_array_get_item at plist.c:667:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
// plist_from_bin at bplist.c:847:13 in plist.h
// plist_access_path at plist.c:1245:9 in plist.h
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
#include <cstdarg>
#include <cstring>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Fuzzing plist_from_openstep
    plist_t plist_openstep = nullptr;
    plist_err_t err_openstep = plist_from_openstep(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist_openstep);
    if (err_openstep == PLIST_ERR_SUCCESS && plist_openstep) {
        // Fuzzing plist_dict_get_size
        plist_dict_get_size(plist_openstep);

        // Fuzzing plist_access_pathv
        uint32_t path_length = 0;
        plist_access_pathv(plist_openstep, path_length, nullptr);

        // Fuzzing plist_array_get_item
        plist_array_get_item(plist_openstep, 0);

        // Clean up
        plist_free(plist_openstep);
    }

    // Fuzzing plist_from_bin
    plist_t plist_bin = nullptr;
    plist_err_t err_bin = plist_from_bin(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist_bin);
    if (err_bin == PLIST_ERR_SUCCESS && plist_bin) {
        // Fuzzing plist_access_path
        plist_access_path(plist_bin, 0);

        // Clean up
        plist_free(plist_bin);
    }

    return 0;
}