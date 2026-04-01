#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the moov_boxes is not NULL and has some data
    u8 *moov_boxes = (u8 *)malloc(size);
    if (!moov_boxes) {
        gf_isom_close(movie);
        return 0;
    }

    // Copy data into moov_boxes
    memcpy(moov_boxes, data, size);

    // Call the function-under-test with different values for udta_only
    gf_isom_load_extra_boxes(movie, moov_boxes, (u32)size, GF_FALSE);
    gf_isom_load_extra_boxes(movie, moov_boxes, (u32)size, GF_TRUE);

    // Clean up
    free(moov_boxes);
    gf_isom_close(movie);

    return 0;
}