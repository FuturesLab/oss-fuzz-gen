#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Initialize the GF_ISOFile structure
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Ensure the data size is sufficient to extract a track number
    if (size < sizeof(uint32_t)) {
        gf_isom_close(the_file);
        return 0;
    }

    // Extract the track number from the input data
    uint32_t trackNumber = *((uint32_t*)data);

    // Call the function under test
    gf_isom_cenc_allocate_storage(the_file, trackNumber);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}