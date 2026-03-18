// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_add_sample_aux_info at isom_write.c:9301:8 in isomedia.h
// gf_isom_set_track_index at isom_write.c:8945:8 in isomedia.h
// gf_isom_get_sample_references at isom_read.c:6727:8 in isomedia.h
// gf_isom_set_nalu_length_field at isom_write.c:8502:8 in isomedia.h
// gf_isom_set_track_id at isom_write.c:5076:8 in isomedia.h
// gf_isom_set_brand_info at isom_write.c:3520:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void dummy_track_num_changed(void *udta, u32 old_track_num, u32 new_track_num) {
    // Dummy callback function for track number changes
}

int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) {
        return 0;
    }

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *) (Data);
    u32 sampleNumber = *(u32 *) (Data + sizeof(u32));
    u32 aux_type = *(u32 *) (Data + 2 * sizeof(u32));
    u32 aux_info = *(u32 *) (Data + 3 * sizeof(u32));
    u8 *aux_data = (u8 *) (Data + 4 * sizeof(u32));
    u32 aux_data_size = Size - 4 * sizeof(u32);

    // Fuzz gf_isom_add_sample_aux_info
    gf_isom_add_sample_aux_info(isom_file, trackNumber, sampleNumber, aux_type, aux_info, aux_data, aux_data_size);

    // Fuzz gf_isom_set_track_index
    gf_isom_set_track_index(isom_file, trackNumber, sampleNumber, dummy_track_num_changed, NULL);

    // Fuzz gf_isom_get_sample_references
    u32 refID, nb_refs;
    const u32 *refs;
    gf_isom_get_sample_references(isom_file, trackNumber, sampleNumber, &refID, &nb_refs, &refs);

    // Fuzz gf_isom_set_nalu_length_field
    gf_isom_set_nalu_length_field(isom_file, trackNumber, sampleNumber, aux_type);

    // Fuzz gf_isom_set_track_id
    gf_isom_set_track_id(isom_file, trackNumber, aux_type);

    // Fuzz gf_isom_set_brand_info
    gf_isom_set_brand_info(isom_file, aux_type, aux_info);

    gf_isom_close(isom_file);
    return 0;
}