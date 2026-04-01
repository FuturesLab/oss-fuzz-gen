// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_text_description at tx3g.c:49:8 in isomedia.h
// gf_isom_get_reference_ID at isom_read.c:1270:8 in isomedia.h
// gf_isom_set_visual_info at isom_write.c:1769:8 in isomedia.h
// gf_isom_get_pcm_config at sample_descs.c:1972:8 in isomedia.h
// gf_isom_get_visual_info at isom_read.c:3821:8 in isomedia.h
// gf_isom_get_dims_description at sample_descs.c:931:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_159(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    // Prepare the dummy file
    write_dummy_file(Data, Size);

    // Initialize variables
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 Width = *((u32 *)(Data + 2 * sizeof(u32)));
    u32 Height = *((u32 *)(Data + 3 * sizeof(u32)));
    u32 referenceType = *((u32 *)(Data + 4 * sizeof(u32)));

    GF_TextSampleDescriptor *text_desc = NULL;
    gf_isom_get_text_description(isom_file, trackNumber, sampleDescriptionIndex, &text_desc);
    if (text_desc) {
        // Free the allocated descriptor
        free(text_desc);
    }

    GF_ISOTrackID refTrackID;
    gf_isom_get_reference_ID(isom_file, trackNumber, referenceType, sampleDescriptionIndex, &refTrackID);

    gf_isom_set_visual_info(isom_file, trackNumber, sampleDescriptionIndex, Width, Height);

    u32 flags, pcm_size;
    gf_isom_get_pcm_config(isom_file, trackNumber, sampleDescriptionIndex, &flags, &pcm_size);

    gf_isom_get_visual_info(isom_file, trackNumber, sampleDescriptionIndex, &Width, &Height);

    GF_DIMSDescription dims_desc;
    gf_isom_get_dims_description(isom_file, trackNumber, sampleDescriptionIndex, &dims_desc);

    // Close the ISO file
    gf_isom_close(isom_file);

    return 0;
}