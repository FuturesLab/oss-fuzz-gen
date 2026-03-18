#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to initialize the parameters
    if (size < sizeof(GF_ISOTrackID) + sizeof(s32) + sizeof(u32)) {
        return 0;
    }

    // Initialize the parameters
    GF_ISOFile *movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL); // Create a temporary ISO file
    if (!movie) {
        return 0;
    }

    GF_ISOTrackID TrackID = (GF_ISOTrackID)data[0]; // Use the first byte for TrackID
    s32 refID = (s32)data[1]; // Use the second byte for refID
    u32 nb_refs = (u32)data[2]; // Use the third byte for nb_refs

    // Ensure there is enough data for the refs array
    if (size < 3 + nb_refs * sizeof(s32)) {
        gf_isom_close(movie);
        return 0;
    }

    s32 *refs = (s32 *)(data + 3); // Use the remaining data for refs

    // Call the function-under-test
    gf_isom_fragment_add_sample_references(movie, TrackID, refID, nb_refs, refs);

    // Clean up
    gf_isom_close(movie);

    return 0;
}