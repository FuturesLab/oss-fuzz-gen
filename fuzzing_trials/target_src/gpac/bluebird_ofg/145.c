#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure that the size is sufficient to extract values for trackNumber and StreamDescriptionIndex
    if (size < 8) {
        gf_isom_close(movie);
        return 0;
    }

    u32 trackNumber = *((u32 *)data);
    u32 StreamDescriptionIndex = *((u32 *)(data + 4));
    Bool remove = (size > 8) ? (Bool)(data[8] % 2) : GF_FALSE;

    // Call the function under test
    gf_isom_set_image_sequence_alpha(movie, trackNumber, StreamDescriptionIndex, remove);

    gf_isom_close(movie);
    return 0;
}