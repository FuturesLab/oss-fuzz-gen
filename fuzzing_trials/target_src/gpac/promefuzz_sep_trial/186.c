// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_media_type at isom_write.c:6188:8 in isomedia.h
// gf_isom_set_audio_layout at isom_write.c:2582:8 in isomedia.h
// gf_isom_set_media_subtype at isom_write.c:6197:8 in isomedia.h
// gf_isom_set_mpegh_compatible_profiles at isom_write.c:9336:8 in isomedia.h
// gf_isom_rewrite_track_dependencies at isom_write.c:5120:8 in isomedia.h
// gf_isom_get_audio_layout at isom_read.c:3919:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_186(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 new_type = *((u32 *)Data + 1);
    u32 sampleDescriptionIndex = *((u32 *)Data + 2);
    u32 nb_compatible_profiles = *((u32 *)Data + 3);

    const u32 *profiles = (Size >= sizeof(u32) * 5) ? (const u32 *)(Data + sizeof(u32) * 4) : NULL;
    GF_AudioChannelLayout layout = {0};

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        write_dummy_file(Data, Size);
        isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    }
    
    if (isom_file) {
        gf_isom_set_media_type(isom_file, trackNumber, new_type);
        gf_isom_set_audio_layout(isom_file, trackNumber, sampleDescriptionIndex, &layout);
        gf_isom_set_media_subtype(isom_file, trackNumber, sampleDescriptionIndex, new_type);
        gf_isom_set_mpegh_compatible_profiles(isom_file, trackNumber, sampleDescriptionIndex, profiles, nb_compatible_profiles);
        gf_isom_rewrite_track_dependencies(isom_file, trackNumber);
        gf_isom_get_audio_layout(isom_file, trackNumber, sampleDescriptionIndex, &layout);

        gf_isom_close(isom_file);
    }

    return 0;
}