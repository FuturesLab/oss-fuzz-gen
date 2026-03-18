// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_reset_switch_parameters at isom_write.c:7015:8 in isomedia.h
// gf_isom_flush_fragments at movie_fragments.c:1468:8 in isomedia.h
// gf_isom_set_byte_offset at isom_read.c:5910:8 in isomedia.h
// gf_isom_reset_alt_brands at isom_write.c:3682:8 in isomedia.h
// gf_isom_enable_mfra at movie_fragments.c:3462:8 in isomedia.h
// gf_isom_switch_source at isom_read.c:6717:8 in isomedia.h
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

#define DUMMY_FILE_PATH "./dummy_file"
#define TMP_DIR_PATH "./"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_178(const uint8_t *Data, size_t Size) {
    // Write data to dummy file
    write_dummy_file(Data, Size);

    // Prepare a dummy ISO file structure
    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, TMP_DIR_PATH);
    if (!isom_file) {
        return 0;
    }

    // Fuzz gf_isom_reset_switch_parameters
    gf_isom_reset_switch_parameters(isom_file);

    // Fuzz gf_isom_flush_fragments
    if (Size > 0) {
        Bool last_segment = Data[0] % 2;
        gf_isom_flush_fragments(isom_file, last_segment);
    }

    // Fuzz gf_isom_set_byte_offset
    if (Size >= sizeof(s64)) {
        s64 byte_offset = *(s64 *)(Data);
        gf_isom_set_byte_offset(isom_file, byte_offset);
    }

    // Fuzz gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(isom_file);

    // Fuzz gf_isom_enable_mfra
    gf_isom_enable_mfra(isom_file);

    // Fuzz gf_isom_switch_source
    if (Size > 0) {
        char *url = (char *)malloc(Size + 1);
        if (url) {
            memcpy(url, Data, Size);
            url[Size] = '\0'; // Null-terminate the string
            gf_isom_switch_source(isom_file, url);
            free(url);
        }
    }

    gf_isom_close(isom_file);
    return 0;
}