#include "/src/gpac/include/gpac/isomedia.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_284(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL); // Open a dummy file
    if (!movie) {
        return 0; // Exit if movie creation fails
    }

    // Ensure that the trackNumber and StreamDescriptionIndex are within reasonable bounds
    u32 trackNumber = size > 0 ? data[0] % 10 : 0; // Use the first byte for trackNumber
    u32 StreamDescriptionIndex = size > 1 ? data[1] % 10 : 0; // Use the second byte for StreamDescriptionIndex

    // Set boolean values using the data
    Bool remove = size > 2 ? data[2] % 2 : 0; // Use the third byte for remove
    Bool all_ref_pics_intra = size > 3 ? data[3] % 2 : 1; // Use the fourth byte for all_ref_pics_intra
    Bool intra_pred_used = size > 4 ? data[4] % 2 : 0; // Use the fifth byte for intra_pred_used

    // Set max_ref_per_pic using the data
    u32 max_ref_per_pic = size > 5 ? data[5] : 1; // Use the sixth byte for max_ref_per_pic

    // Call the function-under-test
    gf_isom_set_image_sequence_coding_constraints(
        movie,
        trackNumber,
        StreamDescriptionIndex,
        remove,
        all_ref_pics_intra,
        intra_pred_used,
        max_ref_per_pic
    );

    // Clean up
    gf_isom_close(movie);

    return 0;
}