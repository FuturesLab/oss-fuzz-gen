// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_interleave_time at isom_write.c:3431:8 in isomedia.h
// gf_isom_get_reference_ID at isom_read.c:1270:8 in isomedia.h
// gf_isom_set_root_od_id at isom_write.c:540:8 in isomedia.h
// gf_isom_set_sample_flags at isom_write.c:8052:8 in isomedia.h
// gf_isom_enable_compression at isom_write.c:2660:8 in isomedia.h
// gf_isom_set_ipod_compatible at isom_write.c:8995:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* open_iso_file(const char* filename) {
    // Dummy function to simulate opening an ISO file
    return gf_isom_open(filename, GF_ISOM_OPEN_WRITE, NULL);
}

static void close_iso_file(GF_ISOFile* isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) {
        return 0;
    }

    GF_ISOFile* isom_file = open_iso_file("./dummy_file");
    if (!isom_file) {
        return 0;
    }

    u32 interleaveTime = *((u32*)Data);
    u32 trackNumber = *((u32*)(Data + 4));
    u32 referenceType = *((u32*)(Data + 8));
    u32 referenceIndex = *((u32*)(Data + 12));
    u32 odID = *((u32*)(Data + 16));

    GF_ISOTrackID refTrackID;
    gf_isom_set_interleave_time(isom_file, interleaveTime);
    gf_isom_get_reference_ID(isom_file, trackNumber, referenceType, referenceIndex, &refTrackID);
    gf_isom_set_root_od_id(isom_file, odID);

    if (Size >= sizeof(u32) * 8) {
        u32 sampleNumber = *((u32*)(Data + 20));
        u32 isLeading = *((u32*)(Data + 24));
        u32 dependsOn = *((u32*)(Data + 28));
        u32 dependedOn = *((u32*)(Data + 32));
        u32 redundant = *((u32*)(Data + 36));

        gf_isom_set_sample_flags(isom_file, trackNumber, sampleNumber, isLeading, dependsOn, dependedOn, redundant);
    }

    if (Size >= sizeof(u32) * 9) {
        u32 compressMode = *((u32*)(Data + 40));
        u32 compressFlags = *((u32*)(Data + 44));

        gf_isom_enable_compression(isom_file, (GF_ISOCompressMode)compressMode, compressFlags);
    }

    gf_isom_set_ipod_compatible(isom_file, trackNumber);

    close_iso_file(isom_file);
    return 0;
}