#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Ensure the input data is non-empty and has a minimum size for a valid MP4 header
    if (size < 8) { // 8 bytes is a typical minimum size for MP4 headers
        return 0;
    }

    GF_ISOFile *the_file = gf_isom_open((const char *)data, GF_ISOM_OPEN_READ, NULL);
    GF_ISOFile *orig_file = gf_isom_open((const char *)data, GF_ISOM_OPEN_READ, NULL);
    u32 trackNumber = 1;
    u32 orig_track = 1;
    u32 orig_desc_index = 1;
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";
    u32 outDescriptionIndex = 0;

    if (the_file && orig_file) {
        gf_isom_clone_sample_description(the_file, trackNumber, orig_file, orig_track, orig_desc_index, URLname, URNname, &outDescriptionIndex);
    }

    if (the_file) {
        gf_isom_close(the_file);
    }
    if (orig_file) {
        gf_isom_close(orig_file);
    }

    return 0;
}