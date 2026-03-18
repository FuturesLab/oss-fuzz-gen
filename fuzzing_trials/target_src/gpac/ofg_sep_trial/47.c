#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber;

    if (size < sizeof(u32)) {
        return 0;
    }

    // Initialize the_file with a valid GF_ISOFile object
    the_file = gf_isom_open((const char*)data, GF_ISOM_OPEN_READ, NULL);
    if (the_file == NULL) {
        return 0;
    }

    // Extract trackNumber from the input data
    trackNumber = *((u32*)data);

    // Call the function-under-test
    gf_isom_remove_cenc_senc_box(the_file, trackNumber);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}