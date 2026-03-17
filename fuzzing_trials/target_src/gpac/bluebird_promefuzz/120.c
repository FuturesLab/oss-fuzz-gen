#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    // Assuming GF_ISOFile is a structure that can be initialized with some function
    GF_ISOFile *isoFile = gf_isom_open("./dummy_file", 0, NULL);
    if (!isoFile)
        return NULL;

    // Simulating some data initialization
    if (Size > 0) {
        FILE *file = fopen("./dummy_file", "wb");
        if (file) {
            fwrite(Data, 1, Size, file);
            fclose(file);
        }
    }

    return isoFile;
}

static void cleanup_iso_file(GF_ISOFile *isoFile) {
    if (!isoFile)
        return;
    gf_isom_close(isoFile);
}

int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isoFile = initialize_iso_file(Data, Size);
    if (!isoFile)
        return 0;

    // Fuzz gf_isom_estimate_size
    u64 estimated_size = gf_isom_estimate_size(isoFile);
    
    // Fuzz gf_isom_get_smooth_next_tfdt
    u64 next_tfdt = gf_isom_get_smooth_next_tfdt(isoFile, 1);
    
    // Fuzz gf_isom_get_duration
    u64 duration = gf_isom_get_duration(isoFile);
    
    // Fuzz gf_isom_get_original_duration
    u64 original_duration = gf_isom_get_original_duration(isoFile);
    
    // Fuzz gf_isom_get_first_mdat_start
    u64 first_mdat_start = gf_isom_get_first_mdat_start(isoFile);
    
    // Fuzz gf_isom_get_unused_box_bytes
    u64 unused_box_bytes = gf_isom_get_unused_box_bytes(isoFile);

    // Clean up
    cleanup_iso_file(isoFile);

    return 0;
}