#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;
    const char *codec_params = "example/codec";

    // Ensure the_file is not NULL
    if (the_file == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_subtitle_set_mime(the_file, trackNumber, StreamDescriptionIndex, codec_params);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}