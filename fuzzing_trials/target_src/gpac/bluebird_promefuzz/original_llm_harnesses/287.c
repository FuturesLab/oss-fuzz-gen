// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_cenc_allocate_storage at drm_sample.c:1142:8 in isomedia.h
// gf_isom_get_tmcd_config at sample_descs.c:1953:8 in isomedia.h
// gf_isom_check_data_reference at isom_read.c:1705:8 in isomedia.h
// gf_isom_add_desc_to_description at isom_write.c:1631:8 in isomedia.h
// gf_isom_remove_stream_description at isom_write.c:909:8 in isomedia.h
// gf_isom_svc_config_del at avc_ext.c:1818:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Allocate memory for the known size of the struct, assuming the size is known
    size_t isofile_size = 1024; // Example size, should be replaced with actual size if known
    GF_ISOFile *file = (GF_ISOFile *)malloc(isofile_size);
    if (file) {
        memset(file, 0, isofile_size);
    }
    return file;
}

static void cleanup_isofile(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

static void fuzz_gf_isom_cenc_allocate_storage(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return;
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return;

    u32 trackNumber = *(u32 *)Data;
    gf_isom_cenc_allocate_storage(isom_file, trackNumber);

    cleanup_isofile(isom_file);
}

static void fuzz_gf_isom_get_tmcd_config(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(u32)) return;
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u32 tmcd_flags, tmcd_fps_num, tmcd_fps_den, tmcd_fpt;

    gf_isom_get_tmcd_config(isom_file, trackNumber, sampleDescriptionIndex, &tmcd_flags, &tmcd_fps_num, &tmcd_fps_den, &tmcd_fpt);

    cleanup_isofile(isom_file);
}

static void fuzz_gf_isom_check_data_reference(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(u32)) return;
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));

    gf_isom_check_data_reference(isom_file, trackNumber, sampleDescriptionIndex);

    cleanup_isofile(isom_file);
}

static void fuzz_gf_isom_add_desc_to_description(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(u32) + sizeof(GF_Descriptor)) return;
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    GF_Descriptor *theDesc = (GF_Descriptor *)(Data + 2 * sizeof(u32));

    gf_isom_add_desc_to_description(isom_file, trackNumber, sampleDescriptionIndex, theDesc);

    cleanup_isofile(isom_file);
}

static void fuzz_gf_isom_remove_stream_description(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(u32)) return;
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));

    gf_isom_remove_stream_description(isom_file, trackNumber, sampleDescriptionIndex);

    cleanup_isofile(isom_file);
}

static void fuzz_gf_isom_svc_config_del(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(u32)) return;
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));

    gf_isom_svc_config_del(isom_file, trackNumber, sampleDescriptionIndex);

    cleanup_isofile(isom_file);
}

int LLVMFuzzerTestOneInput_287(const uint8_t *Data, size_t Size) {
    fuzz_gf_isom_cenc_allocate_storage(Data, Size);
    fuzz_gf_isom_get_tmcd_config(Data, Size);
    fuzz_gf_isom_check_data_reference(Data, Size);
    fuzz_gf_isom_add_desc_to_description(Data, Size);
    fuzz_gf_isom_remove_stream_description(Data, Size);
    fuzz_gf_isom_svc_config_del(Data, Size);
    return 0;
}