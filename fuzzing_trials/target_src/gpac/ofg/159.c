#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a valid string
    if (size < 1) {
        return 0;
    }

    // Initialize a GF_ISOFile instance
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *text = (char *)malloc(size + 1);
    if (!text) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(text, data, size);
    text[size] = '\0';

    // Call the function-under-test
    gf_isom_sdp_add_line(movie, text);

    // Clean up
    free(text);
    gf_isom_close(movie);

    return 0;
}