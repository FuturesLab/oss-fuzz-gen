#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h> // Include this for u32 type

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u32 seg_index;

    // Initialize variables to avoid NULL values
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL); // Open a dummy file for testing
    if (!movie) {
        return 0; // Exit if the file cannot be opened
    }

    // Ensure size is sufficient to extract trackNumber and seg_index
    if (size < sizeof(u32) * 2) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber and seg_index from fuzzing data
    trackNumber = *((u32 *)data);
    seg_index = *((u32 *)(data + sizeof(u32)));

    // Call the function-under-test
    gf_isom_remove_edit(movie, trackNumber, seg_index);

    // Clean up
    gf_isom_close(movie);

    return 0;
}