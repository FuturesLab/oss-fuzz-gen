#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (the_file == NULL) {
        return 0;
    }

    u32 trackNumber = 1;
    u8 *metadata = (u8 *)malloc(size);
    if (metadata == NULL) {
        gf_isom_close(the_file);
        return 0;
    }
    memcpy(metadata, data, size);

    u32 metadata_size = (u32)size;
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";
    u32 outDescriptionIndex = 0;

    gf_isom_flac_config_new(the_file, trackNumber, metadata, metadata_size, URLname, URNname, &outDescriptionIndex);

    free(metadata);
    gf_isom_close(the_file);

    return 0;
}