#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Initialize necessary variables
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = Data[0];
    u32 referenceType = *((u32 *)(Data + 1));
    u32 referenceIndex = Data[2];
    GF_ISOTrackID refTrackID;

    // Fuzz gf_isom_get_reference_ID
    gf_isom_get_reference_ID(isom_file, trackNumber, referenceType, referenceIndex, &refTrackID);

    // Fuzz gf_isom_get_track_matrix
    u32 matrix[9];
    gf_isom_get_track_matrix(isom_file, trackNumber, matrix);

    // Fuzz gf_isom_set_extraction_slc
    GF_SLConfig slConfig = {0};
    gf_isom_set_extraction_slc(isom_file, trackNumber, referenceIndex, &slConfig);

    // Fuzz gf_isom_refresh_size_info
    gf_isom_refresh_size_info(isom_file, trackNumber);

    // Fuzz gf_isom_set_media_type
    gf_isom_set_media_type(isom_file, trackNumber, referenceType);

    // Fuzz gf_isom_set_track_reference
    gf_isom_set_track_reference(isom_file, trackNumber, referenceType, refTrackID);

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}