#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

#ifdef __cplusplus
extern "C" {
#endif

// Fuzzing harness for gf_isom_sdp_add_line
int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Initialize GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *text = (char *)malloc(size + 1);
    if (!text) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(text, data, size);
    text[size] = '\0';

    // Call the function-under-test
    gf_isom_sdp_add_line(movie, text);

    // Cleanup
    free(text);
    gf_isom_close(movie);

    return 0;
}

#ifdef __cplusplus
}
#endif