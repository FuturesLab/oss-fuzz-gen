#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_244(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u64) * 2 + sizeof(Bool)) {
        return 0;
    }

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = NULL;
    u64 missingBytes = 0;
    u64 creationTime = 0, modificationTime = 0;
    u64 currentTopBoxOffset = 0;
    u64 topBoxStart = 0;
    u64 startRange = *(u64 *)Data;
    u64 endRange = *((u64 *)Data + 1);
    Bool enableFragTemplates = *((Bool *)(Data + sizeof(u64) * 2));
    GF_Err err;

    // Test gf_isom_open_progressive
    err = gf_isom_open_progressive("./dummy_file", startRange, endRange, enableFragTemplates, &isom_file, &missingBytes);
    if (err != GF_OK || !isom_file) {
        return 0;
    }

    // Test gf_isom_refresh_fragmented

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of gf_isom_refresh_fragmented
    err = gf_isom_refresh_fragmented(isom_file, &missingBytes, (const char *)Data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Test gf_isom_get_current_top_box_offset
    err = gf_isom_get_current_top_box_offset(isom_file, &currentTopBoxOffset);

    // Test gf_isom_get_creation_time
    err = gf_isom_get_creation_time(isom_file, &creationTime, &modificationTime);

    // Test gf_isom_reset_data_offset
    err = gf_isom_reset_data_offset(isom_file, &topBoxStart);

    // Test gf_isom_open_segment
    err = gf_isom_open_segment(isom_file, "./dummy_file", startRange, endRange, 0);

    // Cleanup
    if (isom_file) {
        gf_isom_close(isom_file);
    }
    return 0;
}