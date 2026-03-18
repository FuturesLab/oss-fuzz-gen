// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_pssh_count at isom_read.c:5559:5 in isomedia.h
// gf_isom_set_inplace_padding at isom_read.c:88:8 in isomedia.h
// gf_isom_open_progressive_ex at isom_read.c:435:8 in isomedia.h
// gf_isom_get_num_supported_boxes at box_funcs.c:1880:5 in isomedia.h
// gf_isom_get_supported_box_type at box_funcs.c:2355:5 in isomedia.h
// gf_isom_segment_get_fragment_size at isom_read.c:927:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

// Dummy size for GF_ISOFile since its actual size is not known
#define DUMMY_ISOFILE_SIZE 1024

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(DUMMY_ISOFILE_SIZE);
    if (isom_file) {
        memset(isom_file, 0, DUMMY_ISOFILE_SIZE);
    }
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = NULL;
    GF_Err err;
    u32 pssh_count;
    u64 fragment_size;
    u32 moof_size;
    u64 BytesMissing;
    u32 topBoxType;
    FILE *file;

    // Create a dummy file if needed
    file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Initialize ISO file structure
    isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    // Fuzz gf_isom_get_pssh_count
    pssh_count = gf_isom_get_pssh_count(isom_file);

    // Fuzz gf_isom_set_inplace_padding
    u32 padding = Size > 0 ? Data[0] : 0;
    err = gf_isom_set_inplace_padding(isom_file, padding);

    // Fuzz gf_isom_open_progressive_ex
    err = gf_isom_open_progressive_ex("./dummy_file", 0, Size, 0, &isom_file, &BytesMissing, &topBoxType);

    // Fuzz gf_isom_get_num_supported_boxes
    u32 num_supported_boxes = gf_isom_get_num_supported_boxes();

    // Fuzz gf_isom_get_supported_box_type
    if (num_supported_boxes > 0) {
        u32 box_type = gf_isom_get_supported_box_type(Data[0] % num_supported_boxes);
    }

    // Fuzz gf_isom_segment_get_fragment_size
    fragment_size = gf_isom_segment_get_fragment_size(isom_file, 1, &moof_size);

    // Cleanup
    cleanup_iso_file(isom_file);

    return 0;
}