// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_meta_primary_item at meta.c:1987:8 in isomedia.h
// gf_isom_set_image_sequence_alpha at isom_write.c:2334:8 in isomedia.h
// gf_isom_update_bitrate_ex at sample_descs.c:1699:8 in isomedia.h
// gf_isom_update_aperture_info at isom_write.c:2179:8 in isomedia.h
// gf_isom_set_composition_offset_mode at isom_write.c:8001:8 in isomedia.h
// gf_isom_use_compact_size at isom_write.c:3448:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4 + sizeof(Bool)) return 0;

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ_EDIT, NULL);
    if (!isom_file) return 0;

    u32 track_num = *((u32 *)Data);
    u32 item_num = *((u32 *)(Data + sizeof(u32)));
    u32 sampleDescriptionIndex = *((u32 *)(Data + 2 * sizeof(u32)));
    u32 bitrates = *((u32 *)(Data + 3 * sizeof(u32)));
    Bool flag = *((Bool *)(Data + 4 * sizeof(u32)));

    // Fuzz gf_isom_set_meta_primary_item
    gf_isom_set_meta_primary_item(isom_file, flag, track_num, item_num);

    // Fuzz gf_isom_set_image_sequence_alpha
    gf_isom_set_image_sequence_alpha(isom_file, track_num, sampleDescriptionIndex, flag);

    // Fuzz gf_isom_update_bitrate_ex
    gf_isom_update_bitrate_ex(isom_file, track_num, sampleDescriptionIndex, bitrates, bitrates, bitrates, flag);

    // Fuzz gf_isom_update_aperture_info
    gf_isom_update_aperture_info(isom_file, track_num, flag);

    // Fuzz gf_isom_set_composition_offset_mode
    gf_isom_set_composition_offset_mode(isom_file, track_num, flag);

    // Fuzz gf_isom_use_compact_size
    gf_isom_use_compact_size(isom_file, track_num, flag);

    gf_isom_close(isom_file);
    return 0;
}