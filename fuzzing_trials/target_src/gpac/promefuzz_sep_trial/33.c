// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_svc_config_del at avc_ext.c:1818:8 in isomedia.h
// gf_isom_set_root_od_id at isom_write.c:540:8 in isomedia.h
// gf_isom_get_alternate_brand at isom_read.c:2648:8 in isomedia.h
// gf_isom_set_media_subtype at isom_write.c:6197:8 in isomedia.h
// gf_isom_add_user_data_boxes at isom_write.c:3856:8 in isomedia.h
// gf_isom_enable_compression at isom_write.c:2660:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_NAME "./dummy_file"

// Helper function to create a dummy ISO file
static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for GF_ISOFile using a dummy allocation size
    GF_ISOFile *iso_file = (GF_ISOFile*)calloc(1, 1024); // Using a generic size for allocation
    return iso_file;
}

// Helper function to write dummy data to a file
static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_NAME, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

// Helper function to clean up ISO file
static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        free(iso_file);
    }
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 7) return 0; // Ensure there's enough data for all parameters

    // Prepare dummy file
    write_dummy_file(Data, Size);

    // Create a dummy ISO file
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Extract parameters from input data
    u32 trackNumber = *(u32*)Data;
    u32 sampleDescriptionIndex = *((u32*)Data + 1);
    u32 OD_ID = *((u32*)Data + 2);
    u32 BrandIndex = *((u32*)Data + 3);
    u32 new_type = *((u32*)Data + 4);
    u32 compress_mode = *((u32*)Data + 5);
    u32 compress_flags = *((u32*)Data + 6);

    // Call target functions with extracted parameters
    gf_isom_svc_config_del(iso_file, trackNumber, sampleDescriptionIndex);
    gf_isom_set_root_od_id(iso_file, OD_ID);

    u32 brand;
    gf_isom_get_alternate_brand(iso_file, BrandIndex, &brand);

    gf_isom_set_media_subtype(iso_file, trackNumber, sampleDescriptionIndex, new_type);

    // Use the remaining data as user data boxes
    if (Size > sizeof(u32) * 7) {
        gf_isom_add_user_data_boxes(iso_file, trackNumber, (u8*)(Data + sizeof(u32) * 7), (u32)(Size - sizeof(u32) * 7));
    }

    gf_isom_enable_compression(iso_file, compress_mode, compress_flags);

    // Cleanup
    cleanup_iso_file(iso_file);
    return 0;
}