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
#include <cstdio>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(SF_INFO)) {
        return 0;
    }

    write_dummy_file(Data, Size);

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    SNDFILE *sndfile = sf_open("./dummy_file", SFM_READ, &sfinfo);
    if (!sndfile) {
        return 0;
    }

    SF_CHUNK_INFO chunk_info;
    memset(&chunk_info, 0, sizeof(SF_CHUNK_INFO));

    SF_CHUNK_ITERATOR *iterator = sf_get_chunk_iterator(sndfile, nullptr);
    if (iterator) {
        while (iterator) {
            sf_get_chunk_data(iterator, &chunk_info);
            sf_get_chunk_size(iterator, &chunk_info);
            iterator = sf_next_chunk_iterator(iterator);
        }
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_get_chunk_iterator to sf_open_virtual
    int ret_sf_close_zynxt = sf_close(sndfile);
    if (ret_sf_close_zynxt < 0){
    	return 0;
    }
    SF_VIRTUAL_IO auufmncw;
    memset(&auufmncw, 0, sizeof(auufmncw));

    SNDFILE* ret_sf_open_virtual_ghwnq = sf_open_virtual(&auufmncw, ret_sf_close_zynxt, NULL, (void *)iterator);
    if (ret_sf_open_virtual_ghwnq == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_set_chunk(sndfile, &chunk_info);

    sf_format_check(&sfinfo);

    sf_close(sndfile);
    return 0;
}