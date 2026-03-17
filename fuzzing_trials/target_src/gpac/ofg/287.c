#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_287(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    char code[4];

    // Initialize the GF_ISOFile structure
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is sufficient to extract required values
    if (size < 8) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber from the input data
    trackNumber = *((u32 *)data);

    // Extract code from the input data, ensuring it's null-terminated
    code[0] = (char)data[4];
    code[1] = (char)data[5];
    code[2] = (char)data[6];
    code[3] = '\0';

    // Call the function-under-test
    gf_isom_set_media_language(movie, trackNumber, code);

    // Clean up
    gf_isom_close(movie);

    return 0;
}