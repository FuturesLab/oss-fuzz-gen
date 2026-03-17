// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_image_sequence_alpha at isom_write.c:2334:8 in isomedia.h
// gf_isom_set_image_sequence_coding_constraints at isom_write.c:2293:8 in isomedia.h
// gf_isom_meta_add_item_ref at meta.c:2005:8 in isomedia.h
// gf_isom_update_bitrate_ex at sample_descs.c:1699:8 in isomedia.h
// gf_isom_tmcd_config_new at sample_descs.c:1784:8 in isomedia.h
// gf_isom_set_composition_offset_mode at isom_write.c:8001:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // We cannot allocate a GF_ISOFile directly since it's an incomplete type.
    // Instead, we use a dummy pointer and assume the library handles its allocation.
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = (Size > 4) ? *(u32 *)(Data + 1) : 0;
    u32 sampleDescriptionIndex = (Size > 8) ? *(u32 *)(Data + 5) : 0;
    Bool remove = (Bool)(Data[0] % 2);

    // Fuzz gf_isom_set_image_sequence_alpha
    gf_isom_set_image_sequence_alpha(iso_file, trackNumber, sampleDescriptionIndex, remove);

    // Fuzz gf_isom_set_image_sequence_coding_constraints
    Bool all_ref_pics_intra = (Bool)((Data[0] >> 1) % 2);
    Bool intra_pred_used = (Bool)((Data[0] >> 2) % 2);
    u32 max_ref_per_pic = (Size > 12) ? *(u32 *)(Data + 9) : 0;
    gf_isom_set_image_sequence_coding_constraints(iso_file, trackNumber, sampleDescriptionIndex, remove, all_ref_pics_intra, intra_pred_used, max_ref_per_pic);

    // Fuzz gf_isom_meta_add_item_ref
    Bool root_meta = (Bool)((Data[0] >> 3) % 2);
    u32 from_id = (Size > 16) ? *(u32 *)(Data + 13) : 0;
    u32 to_id = (Size > 20) ? *(u32 *)(Data + 17) : 0;
    u32 type = (Size > 24) ? *(u32 *)(Data + 21) : 0;
    u64 ref_index = 0;
    gf_isom_meta_add_item_ref(iso_file, root_meta, trackNumber, from_id, to_id, type, &ref_index);

    // Fuzz gf_isom_update_bitrate_ex
    u32 average_bitrate = (Size > 28) ? *(u32 *)(Data + 25) : 0;
    u32 max_bitrate = (Size > 32) ? *(u32 *)(Data + 29) : 0;
    u32 decode_buffer_size = (Size > 36) ? *(u32 *)(Data + 33) : 0;
    Bool forced_for_mpeg4 = (Bool)((Data[0] >> 4) % 2);
    gf_isom_update_bitrate_ex(iso_file, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size, forced_for_mpeg4);

    // Fuzz gf_isom_tmcd_config_new
    u32 fps_num = (Size > 40) ? *(u32 *)(Data + 37) : 0;
    u32 fps_den = (Size > 44) ? *(u32 *)(Data + 41) : 1; // Avoid division by zero
    s32 frames_per_counter_tick = (Size > 48) ? *(s32 *)(Data + 45) : 0;
    Bool is_drop = (Bool)((Data[0] >> 5) % 2);
    Bool is_counter = (Bool)((Data[0] >> 6) % 2);
    u32 outDescriptionIndex = 0;
    gf_isom_tmcd_config_new(iso_file, trackNumber, fps_num, fps_den, frames_per_counter_tick, is_drop, is_counter, &outDescriptionIndex);

    // Fuzz gf_isom_set_composition_offset_mode
    Bool use_negative_offsets = (Bool)((Data[0] >> 7) % 2);
    gf_isom_set_composition_offset_mode(iso_file, trackNumber, use_negative_offsets);

    cleanup_iso_file(iso_file);
    return 0;
}