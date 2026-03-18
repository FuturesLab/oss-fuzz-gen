#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *tempFile = fopen("temp.mp4", "wb");
    if (!tempFile) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    fclose(tempFile);

    // Open the temporary file as an ISO media file
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure trackNumber and sampleNumber are non-zero and within reasonable bounds
    u32 trackNumber = 1;
    u32 sampleNumber = 1;

    // Call the function-under-test
    gf_isom_remove_sample(movie, trackNumber, sampleNumber);

    // Close the movie file
    gf_isom_close(movie);

    // Remove the temporary file
    remove("temp.mp4");

    return 0;
}