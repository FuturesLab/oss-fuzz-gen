#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Ensure trackNumber and DescriptionIndex are within a reasonable range
    u32 trackNumber = (size > 0) ? data[0] % 10 + 1 : 1; // Assuming a small number of tracks
    u32 DescriptionIndex = (size > 1) ? data[1] % 5 + 1 : 1; // Assuming a small number of descriptions
    Bool keep_xps = (size > 2) ? data[2] % 2 : 0;

    // Call the function under test
    gf_isom_vvc_set_inband_config(the_file, trackNumber, DescriptionIndex, keep_xps);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}