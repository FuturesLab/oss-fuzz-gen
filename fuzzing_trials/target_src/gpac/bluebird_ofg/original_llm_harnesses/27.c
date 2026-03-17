#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u64 ctime, mtime;

    // Ensure size is sufficient for extracting values
    if (size < sizeof(u32) + 2 * sizeof(u64)) {
        return 0;
    }

    // Extract values from the data
    trackNumber = *((u32 *)data);
    ctime = *((u64 *)(data + sizeof(u32)));
    mtime = *((u64 *)(data + sizeof(u32) + sizeof(u64)));

    // Create a temporary file for the movie
    char tempFileName[] = "temp_movie.mp4";
    FILE *tempFile = fopen(tempFileName, "wb");
    if (tempFile == NULL) {
        return 0;
    }
    fclose(tempFile);

    // Initialize the movie object
    movie = gf_isom_open(tempFileName, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        remove(tempFileName);
        return 0;
    }

    // Call the function under test with extracted values
    gf_isom_set_track_creation_time(movie, trackNumber, ctime, mtime);

    // Clean up
    gf_isom_close(movie);
    remove(tempFileName);

    return 0;
}