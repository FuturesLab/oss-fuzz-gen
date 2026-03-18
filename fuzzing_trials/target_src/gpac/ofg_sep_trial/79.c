#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to extract trackNumber and ref_type
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *isom_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) {
        return 0;
    }

    // Extract trackNumber and ref_type from the input data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t ref_type = *((uint32_t *)(data + sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_remove_track_reference(isom_file, trackNumber, ref_type);

    // Close the ISO file
    gf_isom_close(isom_file);

    return 0;
}