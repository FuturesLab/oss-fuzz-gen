// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_remove_track_kind at isom_write.c:3185:8 in isomedia.h
// gf_isom_sdp_add_track_line at hint_track.c:740:8 in isomedia.h
// gf_isom_add_track_kind at isom_write.c:3126:8 in isomedia.h
// gf_isom_get_handler_name at isom_read.c:1694:8 in isomedia.h
// gf_isom_set_handler_name at isom_write.c:6060:8 in isomedia.h
// gf_isom_get_track_kind at isom_read.c:1157:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

// Dummy GF_ISOFile size
#define DUMMY_ISOFILE_SIZE 1024

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file structure
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(DUMMY_ISOFILE_SIZE);
    if (!isom_file) return NULL;
    memset(isom_file, 0, DUMMY_ISOFILE_SIZE);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy ISO file
    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    // Prepare track number
    u32 trackNumber = Data[0]; // Use first byte for trackNumber

    // Prepare schemeURI and value as NULL or non-NULL based on input size
    const char *schemeURI = NULL;
    const char *value = NULL;
    if (Size > 2) {
        schemeURI = (const char *)(Data + 1);
        value = (const char *)(Data + 2);
    }

    // Fuzz gf_isom_remove_track_kind
    gf_isom_remove_track_kind(isom_file, trackNumber, schemeURI, value);

    // Fuzz gf_isom_sdp_add_track_line
    const char *sdp_text = (Size > 1) ? (const char *)(Data + 1) : NULL;
    gf_isom_sdp_add_track_line(isom_file, trackNumber, sdp_text);

    // Fuzz gf_isom_add_track_kind
    gf_isom_add_track_kind(isom_file, trackNumber, schemeURI, value);

    // Fuzz gf_isom_get_handler_name
    const char *handlerName = NULL;
    gf_isom_get_handler_name(isom_file, trackNumber, &handlerName);

    // Fuzz gf_isom_set_handler_name
    const char *nameUTF8 = (Size > 1) ? (const char *)(Data + 1) : NULL;
    gf_isom_set_handler_name(isom_file, trackNumber, nameUTF8);

    // Fuzz gf_isom_get_track_kind
    char *scheme = NULL;
    char *kindValue = NULL;
    gf_isom_get_track_kind(isom_file, trackNumber, 1, &scheme, &kindValue);

    // Free allocated memory from gf_isom_get_track_kind
    if (scheme) free(scheme);
    if (kindValue) free(kindValue);

    // Clean up the ISO file
    cleanup_iso_file(isom_file);

    return 0;
}