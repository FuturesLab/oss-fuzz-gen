#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }
    
    u32 trackNumber = 1; // Assuming track number 1 for testing
    u32 StreamDescriptionIndex = 1; // Assuming stream description index 1 for testing
    u32 colour_type = 1; // Arbitrary non-zero value
    u16 colour_primaries = 1; // Arbitrary non-zero value
    u16 transfer_characteristics = 1; // Arbitrary non-zero value
    u16 matrix_coefficients = 1; // Arbitrary non-zero value
    Bool full_range_flag = 1; // Arbitrary non-zero value
    u8 *icc_data = NULL;
    u32 icc_size = 0;

    // Ensure icc_data is not NULL if size is greater than 0
    if (size > 0) {
        icc_data = (u8 *)malloc(size);
        if (icc_data == NULL) {
            gf_isom_close(movie);
            return 0;
        }
        memcpy(icc_data, data, size);
        icc_size = (u32)size;
    }

    // Call the function-under-test
    gf_isom_set_visual_color_info(movie, trackNumber, StreamDescriptionIndex, colour_type, colour_primaries, transfer_characteristics, matrix_coefficients, full_range_flag, icc_data, icc_size);

    // Clean up
    if (icc_data != NULL) {
        free(icc_data);
    }
    gf_isom_close(movie);

    return 0;
}