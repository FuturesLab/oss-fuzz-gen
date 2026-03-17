#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u8 *stsd_data;
    u32 stsd_data_size;

    // Initialize the movie object
    movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is sufficient to extract trackNumber and stsd_data_size
    if (size < sizeof(u32) * 2) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber and stsd_data_size from data
    trackNumber = *(u32 *)data;
    stsd_data_size = *(u32 *)(data + sizeof(u32));

    // Ensure there is enough data for stsd_data
    if (size < sizeof(u32) * 2 + stsd_data_size) {
        gf_isom_close(movie);
        return 0;
    }

    // Point stsd_data to the appropriate location in the input data
    stsd_data = (u8 *)(data + sizeof(u32) * 2);

    // Call the function under test
    gf_isom_set_track_stsd_templates(movie, trackNumber, stsd_data, stsd_data_size);

    // Clean up
    gf_isom_close(movie);

    return 0;
}