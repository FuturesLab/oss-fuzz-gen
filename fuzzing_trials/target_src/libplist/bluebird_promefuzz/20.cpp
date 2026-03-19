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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a plist from memory
    plist_t plist = nullptr;
    plist_format_t format;
    plist_err_t err = plist_from_memory(reinterpret_cast<const char*>(Data), static_cast<uint32_t>(Size), &plist, &format);
    if (err != PLIST_ERR_SUCCESS || !plist) {
        return 0;
    }

    // Define valid options for plist_write functions
    plist_write_options_t options = static_cast<plist_write_options_t>(0);

    // Write the plist to stream
    FILE *stream = fopen("./dummy_file", "w");
    if (stream) {
        plist_write_to_stream(plist, stream, format, options);
        fclose(stream);
    }

    // Write the plist to a file

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of plist_write_to_file
    plist_write_to_file(plist, NULL, format, options);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Write the plist to a string
    char *output = nullptr;
    uint32_t output_length = 0;
    err = plist_write_to_string(plist, &output, &output_length, format, options);
    if (err == PLIST_ERR_SUCCESS && output) {
        plist_mem_free(output);
    }

    // Read the plist from a file
    plist_t file_plist = nullptr;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_write_to_string to plist_string_val_compare_with_size
    plist_t ret_plist_new_null_vibof = plist_new_null();

    int ret_plist_string_val_compare_with_size_lcvfu = plist_string_val_compare_with_size(ret_plist_new_null_vibof, output, 0);
    if (ret_plist_string_val_compare_with_size_lcvfu < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    plist_read_from_file("./dummy_file", &file_plist, nullptr);
    if (file_plist) {
        plist_free(file_plist);
    }

    // Cleanup
    plist_free(plist);

    return 0;
}