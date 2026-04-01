#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "sndfile.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(SF_INFO)) {
        return 0;
    }

    // Initialize SF_INFO structure
    SF_INFO sfinfo;
    std::memcpy(&sfinfo, Data, sizeof(SF_INFO));

    // Validate the SF_INFO structure
    if (!sf_format_check(&sfinfo)) {
        return 0;
    }

    // Create a dummy file to operate on
    const char *dummy_file = "./dummy_file";
    SF_CHUNK_INFO chunk_info;
    std::memset(&chunk_info, 0, sizeof(chunk_info));

    // Open dummy file
    SNDFILE *sndfile = sf_open(dummy_file, SFM_RDWR, &sfinfo);
    if (!sndfile) {
        return 0;
    }

    // Set chunk data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_set_string

    int ret_sf_set_string_glkuh = sf_set_string(sndfile, Size, NULL);
    if (ret_sf_set_string_glkuh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    chunk_info.data = const_cast<uint8_t*>(Data);
    chunk_info.datalen = Size;
    sf_set_chunk(sndfile, &chunk_info);

    // Get chunk iterator
    SF_CHUNK_ITERATOR *iterator = sf_get_chunk_iterator(sndfile, nullptr);
    if (iterator) {
        // Iterate through chunks
        do {
            SF_CHUNK_INFO chunk_info_iter;
            std::memset(&chunk_info_iter, 0, sizeof(chunk_info_iter));

            // Get chunk data
            sf_get_chunk_data(iterator, &chunk_info_iter);

            // Get chunk size
            sf_get_chunk_size(iterator, &chunk_info_iter);

            // Move to next chunk
            iterator = sf_next_chunk_iterator(iterator);
        } while (iterator);
    }

    // Close the sound file
    sf_close(sndfile);

    return 0;
}