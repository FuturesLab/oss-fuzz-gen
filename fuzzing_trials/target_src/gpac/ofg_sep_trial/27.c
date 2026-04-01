#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure there is enough data for required parameters
    if (size < sizeof(u32) * 2 + 1) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *the_file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract trackNumber from data
    u32 trackNumber = *((u32 *)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    // Initialize GF_AC3Config
    GF_AC3Config cfg;
    memset(&cfg, 0, sizeof(GF_AC3Config));

    // Extract URLname and URNname from data
    const char *URLname = (const char *)data;
    size_t url_length = strnlen(URLname, size);
    if (url_length == size) {
        gf_isom_close(the_file);
        return 0;
    }
    data += url_length + 1;
    size -= url_length + 1;

    const char *URNname = (const char *)data;
    size_t urn_length = strnlen(URNname, size);
    if (urn_length == size) {
        gf_isom_close(the_file);
        return 0;
    }
    data += urn_length + 1;
    size -= urn_length + 1;

    // Initialize outDescriptionIndex
    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_ac3_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}