#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;
    u32 colour_type = 1;
    u16 colour_primaries = 1;
    u16 transfer_characteristics = 1;
    u16 matrix_coefficients = 1;
    Bool full_range_flag = GF_TRUE;
    u8 *icc_data = NULL;
    u32 icc_size = 0;

    // Ensure size is sufficient for icc_data
    if (size > 0) {
        icc_data = (u8 *)malloc(size);
        if (icc_data != NULL) {
            memcpy(icc_data, data, size);
            icc_size = size;
        }
    }

    // Call the function under test
    gf_isom_set_visual_color_info(movie, trackNumber, StreamDescriptionIndex, colour_type, 
                                  colour_primaries, transfer_characteristics, 
                                  matrix_coefficients, full_range_flag, icc_data, icc_size);

    // Clean up
    if (icc_data != NULL) {
        free(icc_data);
    }
    gf_isom_close(movie);

    return 0;
}