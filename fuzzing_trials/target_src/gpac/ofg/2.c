#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/src/isomedia/sample_descs.c" // Correct path to include the necessary declarations

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Declare and initialize all necessary variables
    GF_ISOFile *the_file = (GF_ISOFile *) malloc(sizeof(GF_ISOFile));
    u32 trackNumber = 1; // Example track number, can be varied
    GF_AC4Config *cfg = (GF_AC4Config *) malloc(sizeof(GF_AC4Config));
    char URLname[256];
    char URNname[256];
    u32 outDescriptionIndex = 0;

    // Ensure the_file and cfg are not NULL
    if (the_file == NULL || cfg == NULL) {
        free(the_file);
        free(cfg);
        return 0;
    }

    // Initialize URLname and URNname with data from the fuzzing input
    size_t copy_size = size < 255 ? size : 255;
    memcpy(URLname, data, copy_size);
    URLname[copy_size] = '\0';
    memcpy(URNname, data, copy_size);
    URNname[copy_size] = '\0';

    // Call the function-under-test
    gf_isom_ac4_config_new(the_file, trackNumber, cfg, (u8 *)URLname, (u8 *)URNname, &outDescriptionIndex);

    // Clean up allocated memory
    free(the_file);
    free(cfg);

    return 0;
}