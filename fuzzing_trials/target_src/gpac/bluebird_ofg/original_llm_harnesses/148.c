#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        return 0; // Return if the movie cannot be opened
    }

    // Set some default non-zero values for the parameters
    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;
    u32 colour_type = 1;
    u16 colour_primaries = 1;
    u16 transfer_characteristics = 1;
    u16 matrix_coefficients = 1;
    Bool full_range_flag = 1;

    // Use the input data for icc_data and icc_size
    u8 *icc_data = (u8 *)data;
    u32 icc_size = (u32)size;

    // Call the function-under-test
    gf_isom_set_visual_color_info(movie, trackNumber, StreamDescriptionIndex, colour_type, colour_primaries, transfer_characteristics, matrix_coefficients, full_range_flag, icc_data, icc_size);

    // Clean up
    gf_isom_close(movie);

    return 0;
}