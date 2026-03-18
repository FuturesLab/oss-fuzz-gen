// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_track_creation_time at isom_read.c:1004:8 in isomedia.h
// gf_isom_add_chapter at isom_write.c:3227:8 in isomedia.h
// gf_isom_refresh_fragmented at isom_read.c:3088:8 in isomedia.h
// gf_isom_get_media_time at isom_read.c:1342:8 in isomedia.h
// gf_isom_get_chapter at isom_read.c:1551:8 in isomedia.h
// gf_isom_set_track_magic at isom_write.c:8936:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
}

static void release_dummy_iso_file(GF_ISOFile* iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile* iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *((u32*)Data);
    Data += sizeof(u32);
    Size -= sizeof(u32);

    // Fuzz gf_isom_get_track_creation_time
    u64 creationTime, modificationTime;
    gf_isom_get_track_creation_time(iso_file, trackNumber, &creationTime, &modificationTime);

    // Fuzz gf_isom_add_chapter
    if (Size > 0) {
        u64 timestamp = *((u64*)Data);
        Data += sizeof(u64);
        Size -= sizeof(u64);

        char* name = NULL;
        if (Size > 0) {
            name = (char*)malloc(Size + 1);
            if (name) {
                memcpy(name, Data, Size);
                name[Size] = '\0';
            }
        }
        gf_isom_add_chapter(iso_file, trackNumber, timestamp, name);
        if (name) free(name);
    }

    // Fuzz gf_isom_refresh_fragmented
    u64 MissingBytes;
    gf_isom_refresh_fragmented(iso_file, &MissingBytes, NULL);

    // Fuzz gf_isom_get_media_time
    if (Size >= sizeof(u32)) {
        u32 movieTime = *((u32*)Data);
        u64 mediaTime;
        gf_isom_get_media_time(iso_file, trackNumber, movieTime, &mediaTime);
    }

    // Fuzz gf_isom_get_chapter
    if (Size >= sizeof(u32)) {
        u32 Index = *((u32*)Data);
        u64 chapter_time;
        const char* chapter_name;
        gf_isom_get_chapter(iso_file, trackNumber, Index, &chapter_time, &chapter_name);
    }

    // Fuzz gf_isom_set_track_magic
    if (Size >= sizeof(u64)) {
        u64 magic = *((u64*)Data);
        gf_isom_set_track_magic(iso_file, trackNumber, magic);
    }

    release_dummy_iso_file(iso_file);
    return 0;
}