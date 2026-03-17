#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u8 *stsd_data;
    u32 stsd_data_size;

    // Ensure size is sufficient for trackNumber and stsd_data_size
    if (size < sizeof(u32) * 2) {
        return 0;
    }

    // Initialize trackNumber and stsd_data_size from data
    trackNumber = *(u32 *)data;
    stsd_data_size = *(u32 *)(data + sizeof(u32));

    // Ensure stsd_data_size does not exceed remaining data size
    if (size < sizeof(u32) * 2 + stsd_data_size) {
        return 0;
    }

    // Allocate memory for stsd_data
    stsd_data = (u8 *)malloc(stsd_data_size);
    if (stsd_data == NULL) {
        return 0;
    }

    // Copy stsd_data from the input data
    memcpy(stsd_data, data + sizeof(u32) * 2, stsd_data_size);

    // Initialize a dummy GF_ISOFile object
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        free(stsd_data);
        return 0;
    }

    // Call the function under test
    gf_isom_set_track_stsd_templates(movie, trackNumber, stsd_data, stsd_data_size);

    // Clean up
    gf_isom_close(movie);
    free(stsd_data);

    return 0;
}