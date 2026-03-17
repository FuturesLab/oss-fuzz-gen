#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (the_file == NULL) {
        return 0;
    }

    u32 trackNumber = 1;
    GF_VPConfig cfg;
    memset(&cfg, 0, sizeof(GF_VPConfig));

    char URLname[256];
    char URNname[256];
    u32 outDescriptionIndex = 0;
    u32 vpx_type = 0;

    // Ensure URLname and URNname are not NULL
    if (size > 0) {
        size_t urlname_len = size > 255 ? 255 : size;
        memcpy(URLname, data, urlname_len);
        URLname[urlname_len] = '\0';

        size_t urnname_len = size > 255 ? 255 : size;
        memcpy(URNname, data, urnname_len);
        URNname[urnname_len] = '\0';
    } else {
        strcpy(URLname, "http://example.com");
        strcpy(URNname, "urn:example");
    }

    gf_isom_vp_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex, vpx_type);

    gf_isom_close(the_file);

    return 0;
}