#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h> // Make sure to include the GPAC library headers

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 timeScale = 1000; // Initialize a default non-zero timescale

    // Instead of gf_isom_open_from_buffer, use gf_isom_open to create a new GF_ISOFile instance
    // Assume we have a temporary file to work with for fuzzing
    const char *tempFilePath = "/tmp/fuzz_temp.mp4";
    FILE *tempFile = fopen(tempFilePath, "wb");
    if (!tempFile) {
        return 0; // If the temporary file cannot be opened, return
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, tempFile);
    fclose(tempFile);

    // Open the ISO file from the temporary file path
    movie = gf_isom_open(tempFilePath, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0; // If the movie cannot be created, return
    }

    // Call the function-under-test
    gf_isom_set_timescale(movie, timeScale);

    // Clean up
    gf_isom_close(movie);

    return 0;
}