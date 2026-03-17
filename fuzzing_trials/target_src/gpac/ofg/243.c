#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_243(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    s32 subsegs_per_sidx;
    Bool daisy_chain_sidx;
    u32 nb_segs;
    u32 *frags_per_segment;
    u32 *start_range;
    u32 *end_range;
    Bool use_ssix;

    // Initialize the parameters with some values
    movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Return early if movie creation failed
    }

    subsegs_per_sidx = 1;
    daisy_chain_sidx = 1;
    nb_segs = 1;

    // Allocate memory for frags_per_segment, start_range, end_range
    frags_per_segment = (u32 *)malloc(nb_segs * sizeof(u32));
    start_range = (u32 *)malloc(nb_segs * sizeof(u32));
    end_range = (u32 *)malloc(nb_segs * sizeof(u32));

    if (!frags_per_segment || !start_range || !end_range) {
        gf_isom_close(movie);
        free(frags_per_segment);
        free(start_range);
        free(end_range);
        return 0; // Return early if memory allocation failed
    }

    // Initialize the arrays with some values
    for (u32 i = 0; i < nb_segs; i++) {
        frags_per_segment[i] = 1;
        start_range[i] = 0;
        end_range[i] = 1;
    }

    use_ssix = 0;

    // Call the function-under-test
    GF_Err result = gf_isom_allocate_sidx(movie, subsegs_per_sidx, daisy_chain_sidx, nb_segs, frags_per_segment, start_range, end_range, use_ssix);

    // Clean up
    gf_isom_close(movie);
    free(frags_per_segment);
    free(start_range);
    free(end_range);

    return 0;
}