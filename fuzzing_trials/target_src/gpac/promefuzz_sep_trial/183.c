// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_sdp_clean at hint_track.c:884:8 in isomedia.h
// gf_isom_get_sample_references at isom_read.c:6727:8 in isomedia.h
// gf_isom_set_qt_key at isom_write.c:6653:8 in isomedia.h
// gf_isom_enum_udta_keys at isom_read.c:4660:8 in isomedia.h
// gf_isom_rewrite_track_dependencies at isom_write.c:5120:8 in isomedia.h
// gf_isom_sdp_clean_track at hint_track.c:790:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* open_dummy_iso_file() {
    GF_ISOFile *iso_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_183(const uint8_t *Data, size_t Size) {
    // Write data to the dummy file
    FILE *dummy_file = fopen(DUMMY_FILE_PATH, "wb");
    if (!dummy_file) return 0;
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    // Open the dummy ISO file
    GF_ISOFile *iso_file = open_dummy_iso_file();
    if (!iso_file) return 0;

    // Fuzz gf_isom_sdp_clean
    gf_isom_sdp_clean(iso_file);

    // Fuzz gf_isom_get_sample_references
    u32 refID, nb_refs;
    const u32 *refs;
    gf_isom_get_sample_references(iso_file, 1, 1, &refID, &nb_refs, &refs);

    // Fuzz gf_isom_set_qt_key
    GF_QT_UDTAKey *key = NULL;
    gf_isom_set_qt_key(iso_file, key);

    // Fuzz gf_isom_enum_udta_keys
    GF_QT_UDTAKey out_key;
    gf_isom_enum_udta_keys(iso_file, 0, &out_key);

    // Fuzz gf_isom_rewrite_track_dependencies
    gf_isom_rewrite_track_dependencies(iso_file, 1);

    // Fuzz gf_isom_sdp_clean_track
    gf_isom_sdp_clean_track(iso_file, 1);

    // Cleanup
    cleanup_iso_file(iso_file);

    return 0;
}