// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_new_string at plist.c:460:9 in plist.h
// plist_new_string at plist.c:460:9 in plist.h
// plist_string_val_compare at plist.c:1791:5 in plist.h
// plist_key_val_compare at plist.c:1818:5 in plist.h
// plist_string_val_contains at plist.c:1809:5 in plist.h
// plist_string_val_compare_with_size at plist.c:1800:5 in plist.h
// plist_key_val_compare_with_size at plist.c:1827:5 in plist.h
// plist_new_string at plist.c:460:9 in plist.h
// plist_compare_node_value at plist.c:1519:6 in plist.h
// plist_free at plist.c:553:6 in plist.h
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
#include <cstring>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure null-termination for string operations
    std::vector<char> safeData(Data, Data + Size);
    safeData.push_back('\0');

    // Create a dummy PLIST_STRING node
    plist_t plist_string_node = plist_new_string(safeData.data());

    // Create a dummy PLIST_KEY node
    plist_t plist_key_node = plist_new_string(safeData.data());

    // Use part of the data as a comparison string
    const char* cmpval = safeData.data();
    size_t cmpval_size = Size > 1 ? Size - 1 : 0;

    // Fuzz plist_string_val_compare
    plist_string_val_compare(plist_string_node, cmpval);

    // Fuzz plist_key_val_compare
    plist_key_val_compare(plist_key_node, cmpval);

    // Fuzz plist_string_val_contains
    plist_string_val_contains(plist_string_node, cmpval);

    // Fuzz plist_string_val_compare_with_size
    plist_string_val_compare_with_size(plist_string_node, cmpval, cmpval_size);

    // Fuzz plist_key_val_compare_with_size
    plist_key_val_compare_with_size(plist_key_node, cmpval, cmpval_size);

    // Create another dummy PLIST_STRING node for comparison
    plist_t another_plist_string_node = plist_new_string(safeData.data() + cmpval_size);

    // Fuzz plist_compare_node_value
    plist_compare_node_value(plist_string_node, another_plist_string_node);

    // Clean up
    plist_free(plist_string_node);
    plist_free(plist_key_node);
    plist_free(another_plist_string_node);

    return 0;
}