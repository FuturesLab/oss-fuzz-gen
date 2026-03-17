// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_is_track_enabled at isom_read.c:1054:4 in isomedia.h
// gf_isom_add_user_data at isom_write.c:3803:8 in isomedia.h
// gf_isom_has_sync_points at isom_read.c:2603:4 in isomedia.h
// gf_isom_fragment_set_sample_aux_info at isom_write.c:9290:8 in isomedia.h
// gf_isom_get_user_data_count at isom_read.c:2735:5 in isomedia.h
// gf_isom_is_track_in_root_od at isom_read.c:1018:4 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 2 + sizeof(bin128) + 1) {
        return 0;
    }

    GF_ISOFile *isoFile = NULL; // Assume this is properly initialized elsewhere
    u32 trackNumber = *(u32 *)(Data);
    u32 userDataType = *(u32 *)(Data + sizeof(u32));
    bin128 UUID;
    memcpy(&UUID, Data + 2 * sizeof(u32), sizeof(bin128));
    u8 *auxData = (u8 *)(Data + 2 * sizeof(u32) + sizeof(bin128));
    u32 auxDataSize = Size - (2 * sizeof(u32) + sizeof(bin128));

    // Prepare dummy file
    prepare_dummy_file(Data, Size);

    // Fuzz gf_isom_is_track_enabled
    u8 isEnabled = gf_isom_is_track_enabled(isoFile, trackNumber);

    // Fuzz gf_isom_add_user_data
    GF_Err addUserDataErr = gf_isom_add_user_data(isoFile, trackNumber, userDataType, UUID, auxData, auxDataSize);

    // Fuzz gf_isom_has_sync_points
    u8 hasSyncPoints = gf_isom_has_sync_points(isoFile, trackNumber);

    // Fuzz gf_isom_fragment_set_sample_aux_info
    GF_Err setSampleAuxInfoErr = gf_isom_fragment_set_sample_aux_info(isoFile, trackNumber, trackNumber, userDataType, userDataType, auxData, auxDataSize);

    // Fuzz gf_isom_get_user_data_count
    u32 userDataCount = gf_isom_get_user_data_count(isoFile, trackNumber, userDataType, UUID);

    // Fuzz gf_isom_is_track_in_root_od
    u8 isTrackInRootOD = gf_isom_is_track_in_root_od(isoFile, trackNumber);

    // Cleanup actions if necessary
    // (e.g., freeing resources, closing files, etc.)

    return 0;
}