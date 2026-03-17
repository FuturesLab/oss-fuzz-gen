#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Allocate memory for GF_ISOFile using a pointer to an incomplete type
    // Since we don't know the size of GF_ISOFile, we allocate a dummy size
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(100);
    if (!isom_file) return NULL;
    memset(isom_file, 0, 100);
    return isom_file;
}

int LLVMFuzzerTestOneInput_191(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 dummy_value = *((u32 *)(Data + 2 * sizeof(u32)));
    
    GF_DIMSDescription dims_desc;
    memset(&dims_desc, 0, sizeof(GF_DIMSDescription));

    u32 hSpacing, vSpacing, SampleRate, Channels, bitsPerSample;
    u32 outOriginalFormat, outSchemeType, outSchemeVersion;

    // Fuzz gf_isom_get_dims_description
    gf_isom_get_dims_description(isom_file, trackNumber, sampleDescriptionIndex, &dims_desc);

    // Fuzz gf_isom_remove_cenc_senc_box
    gf_isom_remove_cenc_senc_box(isom_file, trackNumber);

    // Fuzz gf_isom_get_pixel_aspect_ratio
    gf_isom_get_pixel_aspect_ratio(isom_file, trackNumber, sampleDescriptionIndex, &hSpacing, &vSpacing);

    // Fuzz gf_isom_get_audio_info
    gf_isom_get_audio_info(isom_file, trackNumber, sampleDescriptionIndex, &SampleRate, &Channels, &bitsPerSample);

    // Fuzz gf_isom_get_cenc_info
    gf_isom_get_cenc_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion);

    // Fuzz gf_isom_remove_stream_description
    gf_isom_remove_stream_description(isom_file, trackNumber, sampleDescriptionIndex);

    free(isom_file);
    return 0;
}