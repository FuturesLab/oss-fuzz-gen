#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h> // Include this to define u32

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to extract u32 values
    if (size < sizeof(u32) * 3) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract u32 values from data
    u32 trackNumber = *((u32 *)data);
    u32 HintDescriptionIndex = *((u32 *)(data + sizeof(u32)));
    u32 TransmissionTime = *((u32 *)(data + 2 * sizeof(u32)));

    // Call the function under test
    gf_isom_begin_hint_sample(the_file, trackNumber, HintDescriptionIndex, TransmissionTime);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}