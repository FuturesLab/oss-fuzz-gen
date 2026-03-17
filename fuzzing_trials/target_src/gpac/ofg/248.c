#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For close() and unlink()
#include <fcntl.h>   // For mkstemp()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
    // Initialize variables for the parameters of gf_isom_get_lpcm_config
    GF_ISOFile *movie;
    u32 trackNumber = 1; // Arbitrary non-zero value
    u32 descriptionIndex = 1; // Arbitrary non-zero value
    Double sample_rate;
    u32 nb_channels;
    u32 flags;
    u32 pcm_size;

    // Create a temporary file to simulate an ISO media file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the ISO media file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        // Clean up the temporary file
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_lpcm_config(movie, trackNumber, descriptionIndex, &sample_rate, &nb_channels, &flags, &pcm_size);

    // Close the movie file
    gf_isom_close(movie);

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}