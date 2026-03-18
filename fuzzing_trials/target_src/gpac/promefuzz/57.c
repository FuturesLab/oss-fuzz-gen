// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_add_sample_group_info at isom_write.c:7555:8 in isomedia.h
// gf_isom_remove_meta_xml at meta.c:678:8 in isomedia.h
// gf_isom_set_meta_type at meta.c:612:8 in isomedia.h
// gf_isom_set_alternate_group_id at isom_write.c:6862:8 in isomedia.h
// gf_isom_reset_track_switch_parameter at isom_write.c:6989:8 in isomedia.h
// gf_isom_set_track_id at isom_write.c:5076:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

#define MY_GF_ISOM_OPEN_READWRITE 0x02 // Assuming the value for read/write mode

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(Bool)) return 0;

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", MY_GF_ISOM_OPEN_READWRITE, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 grouping_type = *((u32 *)(Data + sizeof(u32)));
    Bool is_default = *((Bool *)(Data + sizeof(u32) * 2));
    u32 groupId = *((u32 *)(Data + sizeof(u32) * 2 + sizeof(Bool)));

    Data += sizeof(u32) * 3 + sizeof(Bool);
    Size -= sizeof(u32) * 3 + sizeof(Bool);

    write_dummy_file(Data, Size);

    // Fuzz gf_isom_add_sample_group_info
    u32 sampleGroupDescriptionIndex;
    gf_isom_add_sample_group_info(isom_file, trackNumber, grouping_type, (void *)Data, (u32)Size, is_default, &sampleGroupDescriptionIndex);

    // Fuzz gf_isom_remove_meta_xml
    gf_isom_remove_meta_xml(isom_file, is_default, trackNumber);

    // Fuzz gf_isom_set_meta_type
    gf_isom_set_meta_type(isom_file, is_default, trackNumber, grouping_type);

    // Fuzz gf_isom_set_alternate_group_id
    gf_isom_set_alternate_group_id(isom_file, trackNumber, groupId);

    // Fuzz gf_isom_reset_track_switch_parameter
    gf_isom_reset_track_switch_parameter(isom_file, trackNumber, is_default);

    // Fuzz gf_isom_set_track_id
    gf_isom_set_track_id(isom_file, trackNumber, groupId);

    gf_isom_close(isom_file);

    return 0;
}