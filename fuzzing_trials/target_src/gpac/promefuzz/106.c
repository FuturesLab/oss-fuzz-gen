// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_meta_type at meta.c:43:5 in isomedia.h
// gf_isom_get_meta_item_flags at meta.c:207:5 in isomedia.h
// gf_isom_get_meta_item_by_id at meta.c:219:5 in isomedia.h
// gf_isom_meta_get_item_ref_id at meta.c:2226:5 in isomedia.h
// gf_isom_meta_item_has_ref at meta.c:2203:5 in isomedia.h
// gf_isom_meta_get_item_ref_count at meta.c:2185:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

// Function to create a dummy ISO file
static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the ISO file using the gpac library function
    GF_ISOFile *isoFile = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    return isoFile;
}

// Function to clean up the ISO file
static void cleanup_iso_file(GF_ISOFile *isoFile) {
    if (isoFile) {
        gf_isom_close(isoFile);
    }
}

// Fuzzing entry point
int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isoFile = create_dummy_iso_file(Data, Size);
    if (!isoFile) return 0;

    Bool root_meta = Data[0] % 2 == 0;
    u32 track_num = Size > 1 ? Data[1] : 0;
    u32 item_num = Size > 2 ? Data[2] : 1;
    u32 item_ID = Size > 3 ? Data[3] : 1;
    u32 type = Size > 4 ? Data[4] : 1;
    u32 ref_idx = Size > 5 ? Data[5] : 1;

    // Invoke the API functions with diverse inputs
    u32 meta_type = gf_isom_get_meta_type(isoFile, root_meta, track_num);
    u32 item_flags = gf_isom_get_meta_item_flags(isoFile, root_meta, track_num, item_num);
    u32 item_index = gf_isom_get_meta_item_by_id(isoFile, root_meta, track_num, item_ID);
    u32 ref_id = gf_isom_meta_get_item_ref_id(isoFile, root_meta, track_num, item_ID, type, ref_idx);
    u32 has_ref = gf_isom_meta_item_has_ref(isoFile, root_meta, track_num, item_ID, type);
    u32 ref_count = gf_isom_meta_get_item_ref_count(isoFile, root_meta, track_num, item_ID, type);

    // Use the return values to avoid compiler optimizations
    (void)meta_type;
    (void)item_flags;
    (void)item_index;
    (void)ref_id;
    (void)has_ref;
    (void)ref_count;

    cleanup_iso_file(isoFile);
    return 0;
}