#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a dummy file to write plist data
    FILE *dummy_file = fopen("./dummy_file", "wb+");
    if (!dummy_file) return 0;

    plist_t plist = nullptr;

    // Test plist_from_openstep
    plist_from_openstep(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist);

    // Test plist_write_to_stream
    plist_format_t format = static_cast<plist_format_t>(Data[0] % 3); // Use a small range of formats
    plist_write_options_t options = static_cast<plist_write_options_t>(Data[0] % 2); // Use a small range of options
    plist_write_to_stream(plist, dummy_file, format, options);

    // Test plist_dict_get_size
    if (plist) {
        plist_dict_get_size(plist);
    }

    // Test plist_from_bin
    plist_t plist_bin = nullptr;
    plist_from_bin(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist_bin);

    // Test plist_access_path
    if (plist) {
        plist_access_path(plist, 1, "key");
    }

    // Test plist_array_get_item
    if (plist_bin) {
        plist_array_get_item(plist_bin, 0);
    }

    // Clean up
    if (plist) {
        plist_free(plist);
    }
    if (plist_bin) {
        plist_free(plist_bin);
    }
    fclose(dummy_file);

    return 0;
}