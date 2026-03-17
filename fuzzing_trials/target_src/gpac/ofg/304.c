#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_304(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackID = 1;  // Arbitrary non-zero value
    u32 sample_number_in_frag = 1;  // Arbitrary non-zero value
    u32 aux_type = 1;  // Arbitrary non-zero value
    u32 aux_info = 1;  // Arbitrary non-zero value

    // Ensure the data pointer is non-NULL
    u8 *non_null_data = (u8 *)data;

    // Call the function under test
    GF_Err result = gf_isom_fragment_set_sample_aux_info(movie, trackID, sample_number_in_frag, aux_type, aux_info, non_null_data, (u32)size);

    // Clean up
    gf_isom_close(movie);

    return 0;
}