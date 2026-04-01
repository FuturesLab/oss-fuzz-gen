#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare a dummy plist_t pointer
    plist_t plist = nullptr;

    // Fuzz plist_from_json

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function plist_from_json with plist_from_bin
    plist_from_bin(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function plist_from_bin with plist_from_openstep
    plist_from_openstep(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



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