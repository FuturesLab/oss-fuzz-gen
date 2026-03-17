#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_122(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0; // Ensure there's enough data for basic operations

    // Prepare dummy pointers for ISO files
    GF_ISOFile *isom_file1 = NULL;
    GF_ISOFile *isom_file2 = NULL;

    // Extract parameters from input data
    u32 trackNumber = Data[0];
    u32 sampleDescriptionIndex = Data[1];
    u32 pack_num_samples = Data[2];
    u32 sampleNum = Data[3];
    GF_ISOFragmentBoundaryInfo frag_info;

    // Use the input data to simulate different scenarios
    Bool result1 = gf_isom_is_cenc_media(isom_file1, trackNumber, sampleDescriptionIndex);
    Bool result2 = gf_isom_is_self_contained(isom_file1, trackNumber, sampleDescriptionIndex);
    Bool result3 = gf_isom_is_same_sample_description(isom_file1, trackNumber, sampleDescriptionIndex, isom_file2, trackNumber, sampleDescriptionIndex);
    Bool result4 = gf_isom_enable_raw_pack(isom_file1, trackNumber, pack_num_samples);
    Bool result5 = gf_isom_sample_is_fragment_start(isom_file1, trackNumber, sampleNum, &frag_info);
    Bool result6 = gf_isom_is_omadrm_media(isom_file1, trackNumber, sampleDescriptionIndex);

    // Write the dummy file if needed
    write_dummy_file(Data, Size);

    return 0;
}