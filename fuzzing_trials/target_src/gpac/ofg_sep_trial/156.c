#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        return 0;
    }

    uint8_t *moov_boxes = (uint8_t *)malloc(size);
    if (moov_boxes == NULL) {
        gf_isom_close(movie);
        return 0;
    }

    // Copy input data to moov_boxes
    for (size_t i = 0; i < size; i++) {
        moov_boxes[i] = data[i];
    }

    // Set udta_only to a non-NULL value
    Bool udta_only = false;

    // Call the function under test
    gf_isom_load_extra_boxes(movie, moov_boxes, (uint32_t)size, udta_only);

    // Clean up
    free(moov_boxes);
    gf_isom_close(movie);

    return 0;
}