// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_dict at plist.c:436:9 in plist.h
// plist_new_string at plist.c:460:9 in plist.h
// plist_dict_set_item at plist.c:941:6 in plist.h
// plist_new_array at plist.c:443:9 in plist.h
// plist_new_uint at plist.c:478:9 in plist.h
// plist_array_append_item at plist.c:742:6 in plist.h
// plist_dict_set_item at plist.c:941:6 in plist.h
// plist_from_openstep at oplist.c:926:13 in plist.h
// plist_dict_get_size at plist.c:833:10 in plist.h
// plist_access_path at plist.c:1245:9 in plist.h
// plist_array_get_item at plist.c:667:9 in plist.h
// plist_free at plist.c:553:6 in plist.h
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
#include <cstdarg>
#include <cstring>
#include <plist/plist.h>

static plist_t create_sample_plist() {
    plist_t node = plist_new_dict();
    plist_dict_set_item(node, "key", plist_new_string("value"));
    plist_t array_node = plist_new_array();
    plist_array_append_item(array_node, plist_new_uint(42));
    plist_dict_set_item(node, "array", array_node);
    return node;
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Test plist_from_openstep
    plist_t plist = nullptr;
    plist_err_t err = plist_from_openstep(reinterpret_cast<const char *>(Data), static_cast<uint32_t>(Size), &plist);
    if (err == PLIST_ERR_SUCCESS && plist) {
        // Test plist_dict_get_size
        uint32_t size = plist_dict_get_size(plist);

        // Test plist_access_pathv using a sample plist
        plist_t sample_plist = create_sample_plist();
        const char *path[] = {"key"};
        plist_t accessed_node = plist_access_path(sample_plist, 1, path[0]);

        // Test plist_array_get_item
        plist_t array_item = plist_array_get_item(plist, 0);

        // Clean up plist
        plist_free(plist);
        plist_free(sample_plist);
    }

    // Test plist_from_bin
    plist_t plist_bin = nullptr;
    err = plist_from_bin(reinterpret_cast<const char *>(Data), static_cast<uint32_t>(Size), &plist_bin);
    if (err == PLIST_ERR_SUCCESS && plist_bin) {
        // Test plist_access_path
        plist_t accessed_node = plist_access_path(plist_bin, 1, "key");

        // Clean up plist
        plist_free(plist_bin);
    }

    return 0;
}