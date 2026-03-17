#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    // Create a temporary file to work with
    FILE *tempFile = fopen("temp.mp4", "wb");
    if (!tempFile) {
        return 0;
    }
    fwrite(data, 1, size, tempFile);
    fclose(tempFile);

    // Open the temporary file with read and edit permissions
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_READ_EDIT, NULL);
    if (!movie) {
        return 0;
    }

    // Check if the track exists
    u32 trackNumber = 1; // Assuming track number 1 for testing

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_get_visual_bit_depth
    u32 ret_gf_isom_get_copyright_count_ykvml = gf_isom_get_copyright_count(NULL);
    u16 rtffryvg;
    memset(&rtffryvg, 0, sizeof(rtffryvg));

    GF_Err ret_gf_isom_get_visual_bit_depth_gfbgf = gf_isom_get_visual_bit_depth(movie, 0, ret_gf_isom_get_copyright_count_ykvml, &rtffryvg);

    // End mutation: Producer.APPEND_MUTATOR

    if (gf_isom_get_track_by_id(movie, trackNumber) == 0) {
        gf_isom_close(movie);
        return 0;
    }

    // Prepare the sample
    GF_ISOSample sample;
    sample.data = (u8 *)data;
    sample.dataLength = size;
    sample.DTS = 0;
    sample.CTS_Offset = 0;
    sample.IsRAP = 1; // Random Access Point

    // Call the function-under-test
    gf_isom_add_sample_shadow(movie, trackNumber, &sample);

    // Clean up
    gf_isom_close(movie);

    return 0;
}