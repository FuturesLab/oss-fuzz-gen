#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract necessary parameters
    if (size < sizeof(uint32_t) * 2 + 10) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract trackNumber from data
    uint32_t trackNumber = *(uint32_t *)data;
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Initialize GF_OpusConfig
    GF_OpusConfig cfg;
    memset(&cfg, 0, sizeof(GF_OpusConfig));

    // Allocate and copy URLname from data
    char URLname[5];
    strncpy(URLname, (const char *)data, 4);
    URLname[4] = '\0';
    data += 4;
    size -= 4;

    // Allocate and copy URNname from data
    char URNname[5];
    strncpy(URNname, (const char *)data, 4);
    URNname[4] = '\0';
    data += 4;
    size -= 4;

    // Initialize outDescriptionIndex
    uint32_t outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_opus_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}