#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h> // Include necessary headers for GF_SLConfig and related constants

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Initialize GF_ISOFile
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Ensure the data size is sufficient for trackNumber and StreamDescriptionIndex
    if (size < 8) {
        gf_isom_close(the_file);
        return 0;
    }

    // Extract trackNumber and StreamDescriptionIndex from data
    u32 trackNumber = *(u32 *)data;
    u32 StreamDescriptionIndex = *(u32 *)(data + 4);

    // Initialize GF_SLConfig
    GF_SLConfig slConfig;
    slConfig.timestampResolution = 1000; // Arbitrary non-zero value
    slConfig.timestampLength = 32; // Arbitrary value
    // Removed useTimestamps as it does not exist in GF_SLConfig

    // Call the function-under-test
    gf_isom_set_extraction_slc(the_file, trackNumber, StreamDescriptionIndex, &slConfig);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}