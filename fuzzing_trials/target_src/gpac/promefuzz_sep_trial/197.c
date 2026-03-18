// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_reference_count at isom_read.c:1197:5 in isomedia.h
// gf_isom_set_sample_references at isom_write.c:9510:8 in isomedia.h
// gf_isom_remove_sample at isom_write.c:1541:8 in isomedia.h
// gf_isom_add_sample_info at isom_write.c:7672:8 in isomedia.h
// gf_isom_get_sample_flags at isom_read.c:1913:8 in isomedia.h
// gf_isom_fragment_add_sample_references at movie_fragments.c:3537:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy file named "dummy_file"
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fclose(file);

    // Open the dummy file as a GPAC ISOFile
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_197(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = Data[0];
    u32 referenceType = Data[1];
    u32 sampleNumber = Data[2];
    u32 grouping_type = Data[3];
    u32 sampleGroupDescriptionIndex = 1;
    u32 grouping_type_parameter = 0;
    s32 ID = 1;
    u32 nb_refs = 0;
    s32 refs[1] = {0};

    // Fuzz gf_isom_get_reference_count
    s32 ref_count = gf_isom_get_reference_count(iso_file, trackNumber, referenceType);
    (void)ref_count;

    // Fuzz gf_isom_set_sample_references
    GF_Err set_ref_err = gf_isom_set_sample_references(iso_file, trackNumber, sampleNumber, ID, nb_refs, refs);
    (void)set_ref_err;

    // Fuzz gf_isom_remove_sample
    GF_Err remove_sample_err = gf_isom_remove_sample(iso_file, trackNumber, sampleNumber);
    (void)remove_sample_err;

    // Fuzz gf_isom_add_sample_info
    GF_Err add_sample_info_err = gf_isom_add_sample_info(iso_file, trackNumber, sampleNumber, grouping_type, sampleGroupDescriptionIndex, grouping_type_parameter);
    (void)add_sample_info_err;

    // Fuzz gf_isom_get_sample_flags
    u32 is_leading, dependsOn, dependedOn, redundant;
    GF_Err get_sample_flags_err = gf_isom_get_sample_flags(iso_file, trackNumber, sampleNumber, &is_leading, &dependsOn, &dependedOn, &redundant);
    (void)get_sample_flags_err;

    // Fuzz gf_isom_fragment_add_sample_references
    GF_Err fragment_add_sample_refs_err = gf_isom_fragment_add_sample_references(iso_file, trackNumber, ID, nb_refs, refs);
    (void)fragment_add_sample_refs_err;

    cleanup_iso_file(iso_file);
    return 0;
}