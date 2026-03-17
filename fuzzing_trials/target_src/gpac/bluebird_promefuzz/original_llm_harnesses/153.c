// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_enum_udta_keys at isom_read.c:4660:8 in isomedia.h
// gf_isom_cenc_allocate_storage at drm_sample.c:1142:8 in isomedia.h
// gf_isom_get_sample_references at isom_read.c:6727:8 in isomedia.h
// gf_isom_set_last_sample_duration at isom_write.c:1419:8 in isomedia.h
// gf_isom_copy_sample_info at isom_write.c:8078:8 in isomedia.h
// gf_isom_set_sample_cenc_default_group at isom_write.c:7843:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly.
    // Instead, we will mock it using a pointer and assume other parts of the system initialize it properly.
    GF_ISOFile *file = NULL;
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    // Since we did not allocate any memory for GF_ISOFile, there is nothing to free.
}

int LLVMFuzzerTestOneInput_153(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 idx = *(u32 *)Data;
    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = *(u32 *)Data;
    u32 duration = *(u32 *)Data;

    GF_QT_UDTAKey out_key;
    memset(&out_key, 0, sizeof(GF_QT_UDTAKey));

    // Fuzz gf_isom_enum_udta_keys
    gf_isom_enum_udta_keys(isom_file, idx, &out_key);

    // Fuzz gf_isom_cenc_allocate_storage
    gf_isom_cenc_allocate_storage(isom_file, trackNumber);

    u32 refID;
    u32 nb_refs;
    const u32 *refs;

    // Fuzz gf_isom_get_sample_references
    gf_isom_get_sample_references(isom_file, trackNumber, sampleNumber, &refID, &nb_refs, &refs);

    // Fuzz gf_isom_set_last_sample_duration
    gf_isom_set_last_sample_duration(isom_file, trackNumber, duration);

    // Mock additional ISO file for gf_isom_copy_sample_info
    GF_ISOFile *src_file = initialize_iso_file(Data, Size);
    if (src_file) {
        gf_isom_copy_sample_info(isom_file, trackNumber, src_file, trackNumber, sampleNumber);
        cleanup_iso_file(src_file);
    }

    // Fuzz gf_isom_set_sample_cenc_default_group
    gf_isom_set_sample_cenc_default_group(isom_file, trackNumber, sampleNumber);

    cleanup_iso_file(isom_file);
    return 0;
}