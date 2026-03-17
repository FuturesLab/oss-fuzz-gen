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

int LLVMFuzzerTestOneInput_190(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 7) return 0; // Ensure there is enough data

    GF_ISOFile *isom_file = NULL;
    u32 trackNumber = *((u32 *)Data);
    u32 sampleNumber = *((u32 *)(Data + sizeof(u32)));
    u32 refID = 0, nb_refs = 0;
    const u32 *refs = NULL;

    // Initialize a dummy GF_ISOFile if needed
    // For now, we just simulate the presence of an ISO file by writing a dummy file
    write_dummy_file(Data, Size);

    // Fuzz gf_isom_get_sample_references
    gf_isom_get_sample_references(isom_file, trackNumber, sampleNumber, &refID, &nb_refs, &refs);

    // Fuzz gf_isom_get_reference_ID
    u32 referenceType = *((u32 *)(Data + 2 * sizeof(u32)));
    GF_ISOTrackID refTrackID;
    gf_isom_get_reference_ID(isom_file, trackNumber, referenceType, 1, &refTrackID);

    // Fuzz gf_isom_set_last_sample_duration
    u32 duration = *((u32 *)(Data + 3 * sizeof(u32)));
    gf_isom_set_last_sample_duration(isom_file, trackNumber, duration);

    // Fuzz gf_isom_enable_compression
    GF_ISOCompressMode compress_mode = *((GF_ISOCompressMode *)(Data + 4 * sizeof(u32)));
    u32 compress_flags = *((u32 *)(Data + 5 * sizeof(u32)));
    gf_isom_enable_compression(isom_file, compress_mode, compress_flags);

    // Fuzz gf_isom_get_udts_config
    GF_UDTSConfig cfg;
    gf_isom_get_udts_config(isom_file, trackNumber, sampleNumber, &cfg);

    // Fuzz gf_isom_set_interleave_time
    u32 interleaveTime = *((u32 *)(Data + 6 * sizeof(u32)));
    gf_isom_set_interleave_time(isom_file, interleaveTime);

    // Clean up if necessary
    // For example, if isom_file was dynamically allocated, free it here

    return 0;
}