// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_hint_blank_data at hint_track.c:414:8 in isomedia.h
// gf_isom_remove_edit at isom_write.c:2825:8 in isomedia.h
// gf_isom_add_uuid at isom_write.c:6258:8 in isomedia.h
// gf_isom_get_raw_user_data at isom_write.c:4070:8 in isomedia.h
// gf_isom_add_user_data_boxes at isom_write.c:3856:8 in isomedia.h
// gf_isom_remove_uuid at isom_write.c:6227:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return file;
}

static void free_dummy_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = (Size > 4) ? *(u32*)Data : 1;
    u8 AtBegin = Data[0] % 2;

    // Test gf_isom_hint_blank_data
    gf_isom_hint_blank_data(iso_file, trackNumber, AtBegin);

    // Test gf_isom_remove_edit
    u32 edit_index = (Size > 8) ? *(u32*)(Data + 4) : 1;
    gf_isom_remove_edit(iso_file, trackNumber, edit_index);

    // Test gf_isom_add_uuid
    bin128 UUID;
    memset(&UUID, 0, sizeof(bin128));
    const u8 *uuid_data = (Size > 24) ? Data + 8 : NULL;
    u32 uuid_data_size = (Size > 24) ? Size - 8 : 0;
    gf_isom_add_uuid(iso_file, trackNumber, UUID, uuid_data, uuid_data_size);

    // Test gf_isom_get_raw_user_data
    u8 *output = NULL;
    u32 output_size = 0;
    gf_isom_get_raw_user_data(iso_file, &output, &output_size);
    if (output) {
        free(output);
    }

    // Test gf_isom_add_user_data_boxes
    const u8 *user_data = (Size > 32) ? Data + 16 : NULL;
    u32 user_data_size = (Size > 32) ? Size - 16 : 0;
    gf_isom_add_user_data_boxes(iso_file, trackNumber, (u8 *)user_data, user_data_size);

    // Test gf_isom_remove_uuid
    gf_isom_remove_uuid(iso_file, trackNumber, UUID);

    free_dummy_iso_file(iso_file);
    return 0;
}