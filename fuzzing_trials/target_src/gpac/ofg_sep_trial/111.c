#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    GF_ISOTrackID TrackID;
    u32 orig_dur;
    u32 elapsed_dur;

    // Ensure the size is sufficient to extract required parameters
    if (size < sizeof(GF_ISOTrackID) + 2 * sizeof(u32)) {
        return 0;
    }

    // Initialize movie (assuming a function to create or open a movie is available)
    movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL); // Placeholder for actual movie initialization

    // Extract parameters from the data
    TrackID = *(GF_ISOTrackID *)(data);
    orig_dur = *(u32 *)(data + sizeof(GF_ISOTrackID));
    elapsed_dur = *(u32 *)(data + sizeof(GF_ISOTrackID) + sizeof(u32));

    // Call the function-under-test
    gf_isom_set_fragment_original_duration(movie, TrackID, orig_dur, elapsed_dur);

    // Clean up (assuming a function to close or delete the movie is available)
    gf_isom_close(movie);

    return 0;
}