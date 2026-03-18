#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to extract required values
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize a GF_ISOFile structure
    GF_ISOFile *the_file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract trackNumber and DescriptionIndex from the input data
    uint32_t trackNumber = *(const uint32_t *)data;
    uint32_t DescriptionIndex = *(const uint32_t *)(data + sizeof(uint32_t));

    // Call the function-under-test
    gf_isom_mvc_config_del(the_file, trackNumber, DescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}