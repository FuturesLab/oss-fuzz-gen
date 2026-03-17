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

int LLVMFuzzerTestOneInput_218(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_remove_root_od with gf_isom_last_error
    gf_isom_last_error(iso_file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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