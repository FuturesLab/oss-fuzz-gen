#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4 + sizeof(Bool)) {
        return 0;
    }

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ_EDIT, NULL);
    if (!isom_file) {
        return 0;
    }

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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_use_compact_size with gf_isom_finalize_for_fragment
    gf_isom_finalize_for_fragment(isom_file, track_num, flag);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    gf_isom_close(isom_file);
    return 0;
}