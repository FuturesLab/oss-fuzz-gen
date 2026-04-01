// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_media_original_duration at isom_read.c:1448:5 in isomedia.h
// gf_isom_get_track_duration at isom_read.c:1076:5 in isomedia.h
// gf_isom_get_track_magic at isom_read.c:6160:5 in isomedia.h
// gf_isom_get_missing_bytes at isom_read.c:2482:5 in isomedia.h
// gf_isom_get_current_tfdt at isom_read.c:5822:5 in isomedia.h
// gf_isom_get_media_data_size at isom_read.c:4131:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

// Dummy structure to simulate GF_ISOFile since it's incomplete in the header
typedef struct {
    char *fileName;
    void *moov; // Use void* since the actual type is unknown
} DummyGF_ISOFile;

static DummyGF_ISOFile* create_dummy_isofile(const uint8_t *Data, size_t Size) {
    DummyGF_ISOFile *iso_file = (DummyGF_ISOFile *)malloc(sizeof(DummyGF_ISOFile));
    if (!iso_file) return NULL;

    // Initialize the structure with some dummy values
    memset(iso_file, 0, sizeof(DummyGF_ISOFile));
    iso_file->fileName = "./dummy_file";

    // Write Data to dummy file for file-based operations
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Initialize moov to avoid null pointer dereference
    iso_file->moov = malloc(1); // Allocate a byte to simulate moov
    if (!iso_file->moov) {
        free(iso_file);
        return NULL;
    }
    memset(iso_file->moov, 0, 1);

    return iso_file;
}

static void cleanup_dummy_isofile(DummyGF_ISOFile *iso_file) {
    if (iso_file) {
        if (iso_file->moov) {
            free(iso_file->moov);
        }
        free(iso_file);
    }
}

int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;

    DummyGF_ISOFile *dummy_iso_file = create_dummy_isofile(Data, Size);
    if (!dummy_iso_file) return 0;

    // Cast to GF_ISOFile for API compatibility
    GF_ISOFile *iso_file = (GF_ISOFile *)dummy_iso_file;

    uint32_t trackNumber = *(uint32_t *)Data;

    // Test gf_isom_get_media_original_duration
    u64 duration = gf_isom_get_media_original_duration(iso_file, trackNumber);
    (void)duration; // Suppress unused variable warning

    // Test gf_isom_get_track_duration
    u64 track_duration = gf_isom_get_track_duration(iso_file, trackNumber);
    (void)track_duration;

    // Test gf_isom_get_track_magic
    u64 magic_number = gf_isom_get_track_magic(iso_file, trackNumber);
    (void)magic_number;

    // Test gf_isom_get_missing_bytes
    u64 missing_bytes = gf_isom_get_missing_bytes(iso_file, trackNumber);
    (void)missing_bytes;

    // Test gf_isom_get_current_tfdt
    u64 tfdt = gf_isom_get_current_tfdt(iso_file, trackNumber);
    (void)tfdt;

    // Test gf_isom_get_media_data_size
    u64 media_data_size = gf_isom_get_media_data_size(iso_file, trackNumber);
    (void)media_data_size;

    cleanup_dummy_isofile(dummy_iso_file);
    return 0;
}