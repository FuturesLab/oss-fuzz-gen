#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

#define MY_GF_ISOM_OPEN_READWRITE 0x02 // Assuming the value for read/write mode

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
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