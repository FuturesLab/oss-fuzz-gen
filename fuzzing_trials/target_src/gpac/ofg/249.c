#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber = 1;
    u32 descriptionIndex = 1;
    Double sample_rate = 0.0;
    u32 nb_channels = 0;
    u32 flags = 0;
    u32 pcm_size = 0;

    // Create a temporary ISO file from the input data
    const char *temp_filename = "/tmp/fuzz_movie.mp4";
    FILE *temp_file = fopen(temp_filename, "wb");
    if (!temp_file) return 0;

    fwrite(data, 1, size, temp_file);
    fclose(temp_file);

    // Open the temporary ISO file
    movie = gf_isom_open(temp_filename, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        remove(temp_filename);
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_lpcm_config(movie, trackNumber, descriptionIndex, &sample_rate, &nb_channels, &flags, &pcm_size);

    // Clean up
    gf_isom_close(movie);
    remove(temp_filename);

    return 0;
}