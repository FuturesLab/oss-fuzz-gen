#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_Descriptor* create_descriptor(const uint8_t *Data, size_t Size) {
    GF_Descriptor* descriptor = (GF_Descriptor*)malloc(sizeof(GF_Descriptor));
    if (!descriptor) {
        return NULL;
    }
    memset(descriptor, 0, sizeof(GF_Descriptor));
    descriptor->tag = Data[0]; // Assuming the first byte is a tag.
    return descriptor;
}

int LLVMFuzzerTestOneInput_177(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    GF_ISOFile* iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!iso_file) {
        return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_remove_meta_item
    Bool ret_gf_isom_is_fragmented_efhfz = gf_isom_is_fragmented(NULL);
    u32 ret_gf_isom_get_next_moof_number_zmjvq = gf_isom_get_next_moof_number(iso_file);
    u32 ret_gf_isom_get_timescale_gixas = gf_isom_get_timescale(NULL);
    Bool ret_gf_isom_has_keep_utc_times_mkcri = gf_isom_has_keep_utc_times(iso_file);

    GF_Err ret_gf_isom_remove_meta_item_dpkjp = gf_isom_remove_meta_item(iso_file, ret_gf_isom_is_fragmented_efhfz, ret_gf_isom_get_next_moof_number_zmjvq, ret_gf_isom_get_timescale_gixas, ret_gf_isom_has_keep_utc_times_mkcri, (const char *)"r");

    // End mutation: Producer.APPEND_MUTATOR

    GF_Descriptor* descriptor = create_descriptor(Data, Size);
    if (!descriptor) {
        gf_isom_delete(iso_file);
        return 0;
    }

    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 0;

    // Fuzz gf_isom_add_desc_to_description
    gf_isom_add_desc_to_description(iso_file, trackNumber, sampleDescriptionIndex, descriptor);

    // Fuzz gf_isom_add_desc_to_root_od
    gf_isom_add_desc_to_root_od(iso_file, descriptor);

    // Fuzz gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(iso_file);

    // Fuzz gf_isom_enable_mfra

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_enable_mfra with gf_isom_remove_root_od
    gf_isom_remove_root_od(iso_file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_get_root_od
    GF_Descriptor* root_od = gf_isom_get_root_od(iso_file);
    if (root_od) {
        free(root_od);
    }

    // Clean up
    gf_isom_delete(iso_file);
    free(descriptor);

    return 0;
}