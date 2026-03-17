#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure moov_boxes is not NULL and has some data
    u8 *moov_boxes = (u8 *)malloc(size);
    if (!moov_boxes) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(moov_boxes, data, size);

    // Define moov_boxes_size
    u32 moov_boxes_size = (u32)size;

    // Define udta_only as a Bool (using 0 or 1)
    Bool udta_only = (Bool)(size % 2);

    // Call the function-under-test
    gf_isom_load_extra_boxes(movie, moov_boxes, moov_boxes_size, udta_only);

    // Clean up
    free(moov_boxes);
    gf_isom_close(movie);

    return 0;
}