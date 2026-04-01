#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_333(const uint8_t *data, size_t size) {
    // Initialize the variables required for the function call
    GF_ISOFile *output = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!output) {
        return 0; // Exit if the file cannot be opened
    }

    GF_ISOTrackID TrackID = 1; // Use a valid track ID
    u8 *sai_b = (u8 *)malloc(size);
    if (!sai_b) {
        gf_isom_close(output);
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to sai_b
    for (size_t i = 0; i < size; ++i) {
        sai_b[i] = data[i];
    }

    u32 sai_b_size = (u32)size;
    Bool use_subsamples = 1; // Set to true
    Bool use_saio_32bit = 0; // Set to false
    Bool use_multikey = 1; // Set to true

    // Call the function-under-test
    gf_isom_fragment_set_cenc_sai(output, TrackID, sai_b, sai_b_size, use_subsamples, use_saio_32bit, use_multikey);

    // Clean up
    free(sai_b);
    gf_isom_close(output);

    return 0;
}