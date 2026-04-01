#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) return 0;

    GF_ISOTrackID TrackID = 1;  // Assuming a valid TrackID
    s32 refID = 1;              // Assuming a valid refID
    u32 nb_refs = size / sizeof(s32); // Calculate number of references based on input size

    // Allocate memory for refs and copy data
    s32 *refs = (s32 *)malloc(nb_refs * sizeof(s32));
    if (!refs) {
        gf_isom_close(movie);
        return 0;
    }

    // Copy data into refs
    for (u32 i = 0; i < nb_refs; i++) {
        refs[i] = (s32)data[i % size];
    }

    // Call the function under test
    gf_isom_fragment_add_sample_references(movie, TrackID, refID, nb_refs, refs);

    // Cleanup
    free(refs);
    gf_isom_close(movie);

    return 0;
}