// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_interleave_time at isom_write.c:3431:8 in isomedia.h
// gf_isom_get_reference_ID at isom_read.c:1270:8 in isomedia.h
// gf_isom_get_udta_type at isom_read.c:2711:8 in isomedia.h
// gf_isom_set_ipod_compatible at isom_write.c:8995:8 in isomedia.h
// gf_isom_enable_compression at isom_write.c:2660:8 in isomedia.h
// gf_isom_set_brand_info at isom_write.c:3520:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!iso_file) return NULL;
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (!iso_file) return;
    gf_isom_close(iso_file);
}

int LLVMFuzzerTestOneInput_327(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Fuzz gf_isom_set_interleave_time
    u32 interleaveTime = *((u32*)Data);
    gf_isom_set_interleave_time(iso_file, interleaveTime);

    // Fuzz gf_isom_get_reference_ID
    if (Size >= 4 * sizeof(u32)) {
        u32 trackNumber = *((u32*)(Data + sizeof(u32)));
        u32 referenceType = *((u32*)(Data + 2 * sizeof(u32)));
        u32 referenceIndex = *((u32*)(Data + 3 * sizeof(u32)));
        GF_ISOTrackID refTrackID;
        gf_isom_get_reference_ID(iso_file, trackNumber, referenceType, referenceIndex, &refTrackID);
    }

    // Fuzz gf_isom_get_udta_type
    if (Size >= 3 * sizeof(u32)) {
        u32 trackNumber = *((u32*)(Data + sizeof(u32)));
        u32 udta_idx = *((u32*)(Data + 2 * sizeof(u32)));
        u32 userDataType;
        bin128 UUID;
        gf_isom_get_udta_type(iso_file, trackNumber, udta_idx, &userDataType, UUID);
    }

    // Fuzz gf_isom_set_ipod_compatible
    if (Size >= 2 * sizeof(u32)) {
        u32 trackNumber = *((u32*)(Data + sizeof(u32)));
        gf_isom_set_ipod_compatible(iso_file, trackNumber);
    }

    // Fuzz gf_isom_enable_compression
    if (Size >= 3 * sizeof(u32)) {
        GF_ISOCompressMode compress_mode = (GF_ISOCompressMode)Data[0];
        u32 compress_flags = *((u32*)(Data + sizeof(u32)));
        gf_isom_enable_compression(iso_file, compress_mode, compress_flags);
    }

    // Fuzz gf_isom_set_brand_info
    if (Size >= 3 * sizeof(u32)) {
        u32 majorBrand = *((u32*)(Data + sizeof(u32)));
        u32 minorVersion = *((u32*)(Data + 2 * sizeof(u32)));
        gf_isom_set_brand_info(iso_file, majorBrand, minorVersion);
    }

    cleanup_iso_file(iso_file);
    return 0;
}