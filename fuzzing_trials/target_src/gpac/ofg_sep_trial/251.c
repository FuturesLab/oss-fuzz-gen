#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>  // Include for u32 and Bool types

int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = (size > 0) ? data[0] : 1;
    u32 StreamDescriptionIndex = (size > 1) ? data[1] : 1;
    Bool remove = (size > 2) ? data[2] % 2 : 0;
    Bool all_ref_pics_intra = (size > 3) ? data[3] % 2 : 0;
    Bool intra_pred_used = (size > 4) ? data[4] % 2 : 0;
    u32 max_ref_per_pic = (size > 5) ? data[5] : 1;

    gf_isom_set_image_sequence_coding_constraints(movie, trackNumber, StreamDescriptionIndex, remove, all_ref_pics_intra, intra_pred_used, max_ref_per_pic);

    gf_isom_close(movie);

    return 0;
}