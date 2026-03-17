#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_303(const uint8_t *data, size_t size) {
    // Initialize the parameters for the function-under-test
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL); // Open a dummy file
    if (!movie) {
        return 0; // Exit if the movie cannot be opened
    }

    // Set trackID, sample_number_in_frag, aux_type, aux_info to non-zero values
    u32 trackID = 1;
    u32 sample_number_in_frag = 1;
    u32 aux_type = 1;
    u32 aux_info = 1;

    // Use the provided data and size as the data and size parameters
    u8 *sample_data = (u8 *)data;
    u32 sample_size = (u32)size;

    // Call the function-under-test
    GF_Err result = gf_isom_fragment_set_sample_aux_info(movie, trackID, sample_number_in_frag, aux_type, aux_info, sample_data, sample_size);

    // Clean up
    gf_isom_close(movie);

    return 0;
}