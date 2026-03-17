#include <gpac/isomedia.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;
    Bool remove = GF_FALSE;
    Bool all_ref_pics_intra = GF_FALSE;
    Bool intra_pred_used = GF_FALSE;
    u32 max_ref_per_pic = 0;

    // Ensure the movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_image_sequence_coding_constraints(movie, trackNumber, StreamDescriptionIndex, remove, all_ref_pics_intra, intra_pred_used, max_ref_per_pic);

    // Clean up and close the movie
    gf_isom_close(movie);

    return 0;
}

#ifdef __cplusplus
}
#endif