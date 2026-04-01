// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_add_chapter at isom_write.c:3227:8 in isomedia.h
// gf_isom_set_track_magic at isom_write.c:8936:8 in isomedia.h
// gf_isom_get_chapter at isom_read.c:1551:8 in isomedia.h
// gf_isom_get_media_time at isom_read.c:1342:8 in isomedia.h
// gf_isom_get_track_creation_time at isom_read.c:1004:8 in isomedia.h
// gf_isom_refresh_fragmented at isom_read.c:3088:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate a dummy memory block for GF_ISOFile using a generic pointer
    GF_ISOFile *iso_file = (GF_ISOFile *)malloc(1024); // Assuming 1024 bytes is enough for the dummy
    if (!iso_file) return NULL;
    memset(iso_file, 0, 1024);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        free(iso_file);
    }
}

int LLVMFuzzerTestOneInput_164(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = Data[0] % 5; // Random track number between 0 and 4
    u64 timestamp = 0;
    char *chapter_name = NULL;

    if (Size > 8) {
        timestamp = *((u64 *)(Data + 1)) % 10000; // Random timestamp
    }

    if (Size > 9) {
        chapter_name = (char *)(Data + 9);
    }

    // Fuzz gf_isom_add_chapter
    gf_isom_add_chapter(iso_file, trackNumber, timestamp, chapter_name);

    // Fuzz gf_isom_set_track_magic
    if (Size > 17) {
        u64 magic = *((u64 *)(Data + 9));
        gf_isom_set_track_magic(iso_file, trackNumber, magic);
    }

    // Fuzz gf_isom_get_chapter
    if (Size > 21) {
        u32 chapterIndex = Data[17] % 10; // Random chapter index
        u64 chapter_time;
        const char *retrieved_name;
        gf_isom_get_chapter(iso_file, trackNumber, chapterIndex, &chapter_time, &retrieved_name);
    }

    // Fuzz gf_isom_get_media_time
    if (Size > 25) {
        u32 movieTime = *((u32 *)(Data + 21)) % 5000; // Random movie time
        u64 mediaTime;
        gf_isom_get_media_time(iso_file, trackNumber, movieTime, &mediaTime);
    }

    // Fuzz gf_isom_get_track_creation_time
    if (Size > 33) {
        u64 creationTime, modificationTime;
        gf_isom_get_track_creation_time(iso_file, trackNumber, &creationTime, &modificationTime);
    }

    // Fuzz gf_isom_refresh_fragmented
    if (Size > 41) {
        u64 MissingBytes;
        const char *new_location = (const char *)(Data + 33);
        gf_isom_refresh_fragmented(iso_file, &MissingBytes, new_location);
    }

    cleanup_iso_file(iso_file);
    return 0;
}