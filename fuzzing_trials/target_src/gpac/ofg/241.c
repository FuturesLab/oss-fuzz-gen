#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/setup.h> // Include the correct header for Bool definition

// Remove the typedef for Bool as it conflicts with the existing definition in gpac/setup.h

int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for extracting necessary parameters
    if (size < sizeof(u32) * 2 + sizeof(Bool)) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract parameters from the input data
    u32 trackNumber = *((u32 *)data);
    data += sizeof(u32);

    u32 DescriptionIndex = *((u32 *)data);
    data += sizeof(u32);

    Bool keep_xps = *((Bool *)data);

    // Call the function-under-test
    gf_isom_hevc_set_inband_config(the_file, trackNumber, DescriptionIndex, keep_xps);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}