// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_remove_user_data at isom_write.c:3758:8 in isomedia.h
// gf_isom_get_track_switch_group_count at isom_read.c:4813:8 in isomedia.h
// gf_isom_add_user_data at isom_write.c:3803:8 in isomedia.h
// gf_isom_fragment_set_sample_aux_info at isom_write.c:9290:8 in isomedia.h
// gf_isom_add_user_data_boxes at isom_write.c:3856:8 in isomedia.h
// gf_isom_remove_uuid at isom_write.c:6227:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "isomedia.h"

static void initialize_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        const char *content = "Dummy ISO file content";
        fwrite(content, 1, strlen(content), file);
        fclose(file);
    }
}

static GF_ISOFile* open_iso_file() {
    initialize_dummy_file();
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    GF_ISOFile *iso_file = open_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = 0;
    u32 UserDataType = 0;
    bin128 UUID;
    memset(UUID, 0, sizeof(bin128));

    u32 alternateGroupID = 0;
    u32 nb_groups = 0;

    u8 *data = (u8 *)Data;
    u32 dataSize = (u32)Size;

    // Fuzz gf_isom_remove_user_data
    gf_isom_remove_user_data(iso_file, trackNumber, UserDataType, UUID);

    // Fuzz gf_isom_get_track_switch_group_count
    gf_isom_get_track_switch_group_count(iso_file, trackNumber, &alternateGroupID, &nb_groups);

    // Fuzz gf_isom_add_user_data
    gf_isom_add_user_data(iso_file, trackNumber, UserDataType, UUID, data, dataSize);

    // Fuzz gf_isom_fragment_set_sample_aux_info
    u32 sample_number_in_frag = 1;
    u32 aux_type = 1;
    u32 aux_info = 0;
    gf_isom_fragment_set_sample_aux_info(iso_file, trackNumber, sample_number_in_frag, aux_type, aux_info, data, dataSize);

    // Fuzz gf_isom_add_user_data_boxes
    gf_isom_add_user_data_boxes(iso_file, trackNumber, data, dataSize);

    // Fuzz gf_isom_remove_uuid
    gf_isom_remove_uuid(iso_file, trackNumber, UUID);

    // Cleanup
    gf_isom_close(iso_file);

    return 0;
}