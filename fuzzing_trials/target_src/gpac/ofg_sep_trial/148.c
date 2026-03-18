#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (the_file == NULL) {
        return 0;
    }

    // Ensure trackNumber is non-zero and within a reasonable range
    u32 trackNumber = size > 0 ? (data[0] % 10) + 1 : 1;

    // Call the function-under-test
    gf_isom_set_ipod_compatible(the_file, trackNumber);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}