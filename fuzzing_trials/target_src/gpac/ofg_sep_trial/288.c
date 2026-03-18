#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_288(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    char code[4];

    // Initialize GF_ISOFile
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is sufficient for trackNumber and code
    if (size < sizeof(u32) + 3) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber and code from data
    trackNumber = *((u32 *)data);
    memcpy(code, data + sizeof(u32), 3);
    code[3] = '\0';  // Ensure null-termination for the language code

    // Call the function-under-test
    gf_isom_set_media_language(movie, trackNumber, code);

    // Clean up
    gf_isom_close(movie);

    return 0;
}