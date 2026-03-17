#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void destroy_dummy_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for basic operations

    // Create a dummy ISO file
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = Data[0];
    u32 UserDataType = Data[1];
    u32 sample_number_in_frag = Data[2];
    u32 aux_type = Data[3];
    u32 aux_info = (Size > 4) ? Data[4] : 0;
    u32 dataSize = (Size > 5) ? Size - 5 : 0;
    u8 *data = (dataSize > 0) ? (u8 *)Data + 5 : NULL;
    bin128 UUID;
    memset(UUID, 0, sizeof(UUID));

    // Fuzz gf_isom_is_track_enabled
    u8 track_enabled = gf_isom_is_track_enabled(iso_file, trackNumber);

    // Fuzz gf_isom_add_user_data
    GF_Err add_user_data_err = gf_isom_add_user_data(iso_file, trackNumber, UserDataType, UUID, data, dataSize);

    // Fuzz gf_isom_has_sync_points
    u8 has_sync_points = gf_isom_has_sync_points(iso_file, trackNumber);

    // Fuzz gf_isom_fragment_set_sample_aux_info
    GF_Err set_sample_aux_info_err = gf_isom_fragment_set_sample_aux_info(iso_file, trackNumber, sample_number_in_frag, aux_type, aux_info, data, dataSize);

    // Fuzz gf_isom_get_user_data_count
    u32 user_data_count = gf_isom_get_user_data_count(iso_file, trackNumber, UserDataType, UUID);

    // Fuzz gf_isom_is_track_in_root_od
    u8 is_track_in_root_od = gf_isom_is_track_in_root_od(iso_file, trackNumber);

    destroy_dummy_iso_file(iso_file);

    return 0;
}