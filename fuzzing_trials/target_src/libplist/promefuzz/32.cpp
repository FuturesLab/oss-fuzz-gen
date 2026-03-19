// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_data at plist.c:514:9 in plist.h
// plist_get_data_val at plist.c:1406:6 in plist.h
// plist_mem_free at plist.c:561:6 in plist.h
// plist_get_data_ptr at plist.c:1416:13 in plist.h
// plist_data_val_contains at plist.c:1874:5 in plist.h
// plist_data_val_compare at plist.c:1845:5 in plist.h
// plist_data_val_compare_with_size at plist.c:1862:5 in plist.h
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
#include <cstring>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a PLIST_DATA node from the input data
    plist_t node = plist_new_data(reinterpret_cast<const char*>(Data), Size);
    if (!node) return 0;

    // Test plist_get_data_val
    char *val = nullptr;
    uint64_t length = 0;
    plist_get_data_val(node, &val, &length);
    if (val) plist_mem_free(val);

    // Test plist_get_data_ptr
    const char *data_ptr = plist_get_data_ptr(node, &length);

    // Prepare a comparison buffer
    const uint8_t *cmpval = Data;
    size_t cmpval_size = Size > 1 ? Size / 2 : Size;

    // Test plist_data_val_contains
    int contains = plist_data_val_contains(node, cmpval, cmpval_size);

    // Test plist_data_val_compare
    int compare = plist_data_val_compare(node, cmpval, cmpval_size);

    // Test plist_data_val_compare_with_size
    int compare_with_size = plist_data_val_compare_with_size(node, cmpval, cmpval_size);

    // Free the plist node
    plist_free(node);

    return 0;
}