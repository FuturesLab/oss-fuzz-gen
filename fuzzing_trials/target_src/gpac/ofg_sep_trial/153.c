#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    GF_ISOFile *orig_file = gf_isom_open("dummy_orig.mp4", GF_ISOM_OPEN_WRITE, NULL);

    if (the_file == NULL || orig_file == NULL) {
        return 0;
    }

    u32 trackNumber = 1;
    u32 orig_track = 1;
    u32 orig_desc_index = 1;
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";
    u32 outDescriptionIndex = 0;

    gf_isom_clone_sample_description(the_file, trackNumber, orig_file, orig_track, orig_desc_index, URLname, URNname, &outDescriptionIndex);

    gf_isom_close(the_file);
    gf_isom_close(orig_file);

    return 0;
}