#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly
    // Here we assume a function or method exists to create or open an ISO file
    GF_ISOFile *isoFile = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isoFile) return NULL;

    // Write the data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        gf_isom_close(isoFile);
        return NULL;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    return isoFile;
}

static void cleanup_iso_file(GF_ISOFile *isoFile) {
    if (isoFile) {
        // Remove the dummy file
        remove("./dummy_file");
        gf_isom_close(isoFile);
    }
}

int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isoFile = initialize_iso_file(Data, Size);
    if (!isoFile) return 0;

    u32 trackNumber = *((u32*)Data);

    // Invoke the target functions
    u64 duration1 = gf_isom_get_media_original_duration(isoFile, trackNumber);
    u64 duration2 = gf_isom_get_duration(isoFile);
    u64 duration3 = gf_isom_get_media_duration(isoFile, trackNumber);
    u64 duration4 = gf_isom_get_track_duration_orig(isoFile, trackNumber);
    u64 duration5 = gf_isom_get_original_duration(isoFile);
    u64 duration6 = gf_isom_get_fragmented_duration(isoFile);

    // Handle the return values if necessary, e.g., logging or assertions
    // For this fuzz driver, we simply call the functions

    cleanup_iso_file(isoFile);
    return 0;
}