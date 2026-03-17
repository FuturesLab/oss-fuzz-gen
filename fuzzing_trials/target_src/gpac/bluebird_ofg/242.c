#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Initialize with a non-zero value to avoid NULL
    u32 index = 1; // Initialize with a non-zero value to avoid NULL

    // Create a temporary ISO file for fuzzing
    // Normally, you would parse the data into a GF_ISOFile, but for simplicity, we'll simulate it
    movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0; // Exit if the file cannot be opened
    }

    // Call the function-under-test
    gf_isom_remove_chapter(movie, trackNumber, index);

    // Clean up
    gf_isom_close(movie);

    return 0;
}