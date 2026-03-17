#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        // Perform any necessary cleanup
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) {
        return 0;
    }

    // Prepare dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    // Open the ISO file
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    // Fuzz gf_isom_wma_enum_tag
    char *out_tag = NULL;
    const u8 *data = NULL;
    u32 data_len = 0, version = 0, data_type = 0;
    gf_isom_wma_enum_tag(isom_file, 0, &out_tag, &data, &data_len, &version, &data_type);

    // Fuzz gf_isom_set_track_group
    u32 trackNumber = 0, track_group_id = 0, group_type = 0;
    Bool do_add = GF_FALSE;
    gf_isom_set_track_group(isom_file, trackNumber, track_group_id, group_type, do_add);

    // Fuzz gf_isom_remove_cenc_seig_sample_group

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_remove_cenc_seig_sample_group with gf_isom_add_track_to_root_od
    gf_isom_add_track_to_root_od(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_set_image_sequence_alpha
    u32 sampleDescriptionIndex = 0;
    Bool remove = GF_FALSE;
    gf_isom_set_image_sequence_alpha(isom_file, trackNumber, sampleDescriptionIndex, remove);

    // Fuzz gf_isom_purge_track_reference
    gf_isom_purge_track_reference(isom_file, trackNumber);

    // Fuzz gf_isom_enum_sample_group
    u32 sample_number = 0;
    u32 sgrp_idx = 0, sgrp_type = 0, sgrp_flags = 0, sgrp_parameter = 0;
    u8 *sgrp_data = NULL;
    u32 sgrp_size = 0;
    gf_isom_enum_sample_group(isom_file, trackNumber, sample_number, &sgrp_idx, &sgrp_type, &sgrp_flags, &sgrp_parameter, &sgrp_data, &sgrp_size);
    free(sgrp_data);

    cleanup_iso_file(isom_file);
    return 0;
}