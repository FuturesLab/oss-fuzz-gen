#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <stdio.h>
#include <stdlib.h>

// Function to write data to a temporary file
static char* write_to_temp_file(const uint8_t *data, size_t size) {
    char *filename = tmpnam(NULL);
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return NULL;
    }
    fwrite(data, 1, size, file);
    fclose(file);
    return filename;
}

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u64 dur;
    char *filename;

    // Write data to a temporary file and open it
    filename = write_to_temp_file(data, size);
    if (!filename) {
        return 0;
    }

    // Open the file using gf_isom_open
    movie = gf_isom_open(filename, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        remove(filename);
        return 0;
    }

    // Ensure trackNumber is within a reasonable range
    trackNumber = size > 0 ? (data[0] % 10) + 1 : 1; // Example: limit to 10 tracks

    // Set a non-zero duration
    dur = size > 1 ? (u64)data[1] + 1 : 1;

    // Call the function-under-test
    gf_isom_force_track_duration(movie, trackNumber, dur);

    // Clean up
    gf_isom_close(movie);
    remove(filename);

    return 0;
}