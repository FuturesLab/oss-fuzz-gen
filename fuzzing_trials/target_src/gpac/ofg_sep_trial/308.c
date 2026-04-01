#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_308(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1;
    u8 IsRandomAccessPoint = 1;

    // Create a new ISO file for testing
    the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_end_hint_sample(the_file, trackNumber, IsRandomAccessPoint);

    // Clean up and close the file
    gf_isom_close(the_file);

    return 0;
}

#ifdef __cplusplus
}
#endif