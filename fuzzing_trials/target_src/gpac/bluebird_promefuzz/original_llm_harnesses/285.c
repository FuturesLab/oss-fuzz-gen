// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_set_qt_key at isom_write.c:6653:8 in isomedia.h
// gf_isom_set_qt_key at isom_write.c:6653:8 in isomedia.h
// gf_isom_freeze_order at isom_read.c:76:8 in isomedia.h
// gf_isom_make_interleave at isom_write.c:6051:8 in isomedia.h
// gf_isom_reset_alt_brands at isom_write.c:3682:8 in isomedia.h
// gf_isom_enable_mfra at movie_fragments.c:3462:8 in isomedia.h
// gf_isom_last_error at isom_read.c:46:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile *create_dummy_iso_file() {
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static GF_QT_UDTAKey *create_dummy_qt_key(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(GF_QT_UDTAKey)) return NULL;
    GF_QT_UDTAKey *key = (GF_QT_UDTAKey *)malloc(sizeof(GF_QT_UDTAKey));
    if (!key) return NULL;
    // Initialize the key with data if possible
    memcpy(key, Data, sizeof(GF_QT_UDTAKey));
    return key;
}

int LLVMFuzzerTestOneInput_285(const uint8_t *Data, size_t Size) {
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    GF_QT_UDTAKey *qt_key = create_dummy_qt_key(Data, Size);

    // Fuzz gf_isom_set_qt_key
    gf_isom_set_qt_key(iso_file, qt_key);
    gf_isom_set_qt_key(iso_file, NULL);

    // Fuzz gf_isom_freeze_order
    gf_isom_freeze_order(iso_file);

    // Fuzz gf_isom_make_interleave
    if (Size >= sizeof(Double)) {
        Double time_in_sec;
        memcpy(&time_in_sec, Data, sizeof(Double));
        gf_isom_make_interleave(iso_file, time_in_sec);
    }

    // Fuzz gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(iso_file);

    // Fuzz gf_isom_enable_mfra
    gf_isom_enable_mfra(iso_file);

    // Fuzz gf_isom_last_error
    gf_isom_last_error(iso_file);

    // Cleanup
    free(qt_key);
    gf_isom_close(iso_file);

    return 0;
}