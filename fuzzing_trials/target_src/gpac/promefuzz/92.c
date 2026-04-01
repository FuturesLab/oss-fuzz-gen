// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_dump_ismacryp_sample at box_dump.c:4598:8 in isomedia.h
// gf_isom_add_sample_info at isom_write.c:7672:8 in isomedia.h
// gf_isom_remove_track at isom_write.c:2942:8 in isomedia.h
// gf_isom_text_dump at box_dump.c:4470:8 in isomedia.h
// gf_isom_dump_hint_sample at box_dump.c:3460:8 in isomedia.h
// gf_isom_set_forced_text at tx3g.c:973:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void cleanup_isofile(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) return 0;

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    FILE *dummy_file = fopen("./dummy_file", "wb+");
    if (!dummy_file) {
        cleanup_isofile(isom_file);
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 sampleNumber = *((u32 *)Data + 1);
    u32 grouping_type = *((u32 *)Data + 2);
    u32 sampleGroupDescriptionIndex = *((u32 *)Data + 3);
    u32 grouping_type_parameter = *((u32 *)Data + 4);

    gf_isom_dump_ismacryp_sample(isom_file, trackNumber, sampleNumber, dummy_file);
    gf_isom_add_sample_info(isom_file, trackNumber, sampleNumber, grouping_type, sampleGroupDescriptionIndex, grouping_type_parameter);
    gf_isom_remove_track(isom_file, trackNumber);
    gf_isom_text_dump(isom_file, trackNumber, dummy_file, (GF_TextDumpType)(grouping_type % 3));
    gf_isom_dump_hint_sample(isom_file, trackNumber, sampleNumber, dummy_file);
    gf_isom_set_forced_text(isom_file, trackNumber, sampleGroupDescriptionIndex, grouping_type_parameter % 3);

    fclose(dummy_file);
    cleanup_isofile(isom_file);
    return 0;
}