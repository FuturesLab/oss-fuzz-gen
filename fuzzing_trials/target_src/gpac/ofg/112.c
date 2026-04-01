#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Exit if movie creation fails
    }

    u8 *moov_boxes = (u8 *)data; // Use the input data as moov_boxes
    u32 moov_boxes_size = (u32)size; // Set moov_boxes_size to the size of the input data
    Bool udta_only = GF_FALSE; // Initialize udta_only to GF_FALSE

    // Call the function-under-test
    gf_isom_load_extra_boxes(movie, moov_boxes, moov_boxes_size, udta_only);

    // Clean up
    gf_isom_close(movie);

    return 0;
}