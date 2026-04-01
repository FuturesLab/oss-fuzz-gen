// This fuzz driver is generated for library libplist, aiming to fuzz the following functions:
// plist_from_json at jplist.c:835:13 in plist.h
// plist_write_to_stream at plist.c:1996:13 in plist.h
// plist_from_memory at plist.c:225:13 in plist.h
// plist_from_bin at bplist.c:847:13 in plist.h
// plist_read_from_file at plist.c:306:13 in plist.h
// plist_free at plist.c:553:6 in plist.h
// libplist_version at plist.c:2059:13 in plist.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy plist_t pointer
    plist_t plist = nullptr;

    // Fuzz plist_from_json
    plist_from_json(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist);

    // Prepare a dummy file for plist_write_to_stream
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        // Fuzz plist_write_to_stream with different formats
        plist_format_t formats[] = { PLIST_FORMAT_XML, PLIST_FORMAT_BINARY, PLIST_FORMAT_JSON };
        plist_write_options_t options = static_cast<plist_write_options_t>(0);

        for (auto format : formats) {
            plist_write_to_stream(plist, file, format, options);
        }

        fclose(file);
    }

    // Fuzz plist_from_memory
    plist_format_t detected_format;
    plist_from_memory(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist, &detected_format);

    // Fuzz plist_from_bin
    plist_from_bin(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist);

    // Fuzz plist_read_from_file
    plist_read_from_file("./dummy_file", &plist, &detected_format);

    // Clean up plist if it was created
    if (plist) {
        plist_free(plist);
    }

    // Use libplist_version for logging or compatibility checks
    const char* version = libplist_version();

    return 0;
}