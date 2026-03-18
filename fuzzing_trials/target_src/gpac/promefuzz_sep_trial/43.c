// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_is_ismacryp_media at drm_sample.c:218:6 in isomedia.h
// gf_isom_is_external_track at isom_read.c:6656:6 in isomedia.h
// gf_isom_get_meta_item_count at meta.c:123:5 in isomedia.h
// gf_isom_has_segment at isom_read.c:843:6 in isomedia.h
// gf_isom_is_omadrm_media at drm_sample.c:237:6 in isomedia.h
// gf_isom_meta_get_item_ref_count at meta.c:2185:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* open_dummy_iso_file() {
    // Open a dummy ISO file for testing
    FILE *file = fopen("./dummy_file", "wb+");
    if (!file) return NULL;

    // Write some dummy data to the file
    const char *dummy_data = "dummy data";
    fwrite(dummy_data, 1, strlen(dummy_data), file);
    fflush(file);

    // Create a GF_ISOFile structure
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        fclose(file);
        return NULL;
    }

    return isom_file;
}

static void close_dummy_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
    remove("./dummy_file");
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0; // Ensure there's enough data for indices

    GF_ISOFile *isom_file = open_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 track_num = *((u32 *)(Data + 2 * sizeof(u32)));

    // Fuzz gf_isom_is_ismacryp_media
    Bool is_ismacryp = gf_isom_is_ismacryp_media(isom_file, trackNumber, sampleDescriptionIndex);
    
    // Fuzz gf_isom_is_external_track
    GF_ISOTrackID tkid;
    u32 type, flags;
    const char *location;
    Bool is_external = gf_isom_is_external_track(isom_file, trackNumber, &tkid, &type, &flags, &location);

    // Fuzz gf_isom_get_meta_item_count
    Bool root_meta = (Size > 3 * sizeof(u32)) ? Data[3 * sizeof(u32)] % 2 : GF_FALSE;
    u32 meta_item_count = gf_isom_get_meta_item_count(isom_file, root_meta, track_num);

    // Fuzz gf_isom_has_segment
    u32 brand, version;
    Bool has_segment = gf_isom_has_segment(isom_file, &brand, &version);

    // Fuzz gf_isom_is_omadrm_media
    Bool is_omadrm = gf_isom_is_omadrm_media(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_meta_get_item_ref_count
    u32 from_id = (Size > 4 * sizeof(u32)) ? *((u32 *)(Data + 3 * sizeof(u32))) : 0;
    u32 type_ref = (Size > 5 * sizeof(u32)) ? *((u32 *)(Data + 4 * sizeof(u32))) : 0;
    u32 item_ref_count = gf_isom_meta_get_item_ref_count(isom_file, root_meta, track_num, from_id, type_ref);

    close_dummy_iso_file(isom_file);
    return 0;
}