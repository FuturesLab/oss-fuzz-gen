// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_avc_config_new at avc_ext.c:1575:8 in isomedia.h
// gf_isom_get_data_reference at isom_read.c:1723:8 in isomedia.h
// gf_isom_sdp_get at hint_track.c:909:8 in isomedia.h
// gf_isom_mvc_config_new at avc_ext.c:1882:8 in isomedia.h
// gf_isom_new_dims_description at sample_descs.c:962:8 in isomedia.h
// gf_isom_svc_config_new at avc_ext.c:1876:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // As the structure is incomplete, we can't allocate it directly.
    // Normally, we'd use a proper constructor function from the library.
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = 1;
    GF_AVCConfig *avc_config = NULL;
    GF_DIMSDescription *dims_desc = NULL;
    const char *URLname = NULL;
    const char *URNname = NULL;
    u32 outDescriptionIndex = 0;
    const char *outURL = NULL;
    const char *outURN = NULL;
    const char *sdp = NULL;
    u32 length = 0;

    // Fuzz gf_isom_avc_config_new
    gf_isom_avc_config_new(iso_file, trackNumber, avc_config, URLname, URNname, &outDescriptionIndex);

    // Fuzz gf_isom_get_data_reference
    gf_isom_get_data_reference(iso_file, trackNumber, 1, &outURL, &outURN);

    // Fuzz gf_isom_sdp_get
    gf_isom_sdp_get(iso_file, &sdp, &length);

    // Fuzz gf_isom_mvc_config_new
    gf_isom_mvc_config_new(iso_file, trackNumber, avc_config, URLname, URNname, &outDescriptionIndex);

    // Fuzz gf_isom_new_dims_description
    gf_isom_new_dims_description(iso_file, trackNumber, dims_desc, URLname, URNname, &outDescriptionIndex);

    // Fuzz gf_isom_svc_config_new
    gf_isom_svc_config_new(iso_file, trackNumber, avc_config, URLname, URNname, &outDescriptionIndex);

    cleanup_iso_file(iso_file);
    return 0;
}