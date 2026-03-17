#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 track = 1;
    u32 sampleDescriptionIndex = 1;
    u16 rvc_predefined = 0;
    char mime[] = "video/mp4";
    u8 *data_copy = NULL;
    u32 data_size = size;

    // Ensure the movie is not NULL
    if (!movie) {
        return 0;
    }

    // Copy the input data to a mutable buffer
    if (size > 0) {
        data_copy = (u8 *)malloc(size);
        if (!data_copy) {
            gf_isom_close(movie);
            return 0;
        }
        memcpy(data_copy, data, size);
    }

    // Call the function-under-test
    gf_isom_set_rvc_config(movie, track, sampleDescriptionIndex, rvc_predefined, mime, data_copy, data_size);

    // Clean up
    if (data_copy) {
        free(data_copy);
    }
    gf_isom_close(movie);

    return 0;
}