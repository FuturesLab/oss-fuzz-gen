#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h" // Include this for the u32 type definition

int LLVMFuzzerTestOneInput_218(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is sufficient to extract a track number and a language code
    if (size < 8) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract track number from data
    u32 trackNumber = *(u32 *)data;

    // Extract language code from data
    char code[4];
    memcpy(code, data + 4, 3);
    code[3] = '\0'; // Ensure null-termination

    // Call the function-under-test
    gf_isom_set_media_language(movie, trackNumber, code);

    // Clean up
    gf_isom_close(movie);

    return 0;
}