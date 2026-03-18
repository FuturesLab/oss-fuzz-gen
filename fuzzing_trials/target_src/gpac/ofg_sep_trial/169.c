#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for splitting into parts
    if (size < sizeof(GF_ISOTrackID) + sizeof(u8) + 1) {
        return 0;
    }

    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract TrackID, PaddingBits, and data
    GF_ISOTrackID TrackID = *(GF_ISOTrackID *)data;
    u8 PaddingBits = *(u8 *)(data + sizeof(GF_ISOTrackID));
    u8 *data_ptr = (u8 *)(data + sizeof(GF_ISOTrackID) + sizeof(u8));
    u32 data_size = size - (sizeof(GF_ISOTrackID) + sizeof(u8));

    // Ensure data_ptr is not null and data_size is valid
    if (data_ptr == NULL || data_size == 0) {
        gf_isom_close(movie);
        return 0;
    }

    // Call the function-under-test
    if (gf_isom_fragment_append_data(movie, TrackID, data_ptr, data_size, PaddingBits) != GF_OK) {
        gf_isom_close(movie);
        return 0;
    }

    // Clean up
    gf_isom_close(movie);

    return 0;
}