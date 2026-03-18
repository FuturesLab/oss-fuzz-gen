#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract two u32 values
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract trackNumber and DescriptionIndex from the input data
    uint32_t trackNumber = *((uint32_t*)data);
    uint32_t DescriptionIndex = *((uint32_t*)(data + sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_svc_config_del(the_file, trackNumber, DescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}