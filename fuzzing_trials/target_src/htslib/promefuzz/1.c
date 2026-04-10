// This fuzz driver is generated for library htslib, aiming to fuzz the following functions:
// hopen at hfile.c:1304:8 in hfile.h
// hts_hopen at hts.c:1463:10 in hts.h
// hclose at hfile.c:490:5 in hfile.h
// sam_hdr_read at sam.c:1920:12 in sam.h
// sam_hdr_destroy at sam.c:117:6 in sam.h
// hts_close at hts.c:1639:5 in hts.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <hts.h>
#include <hfile.h>
#include <sam.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file(Data, Size);

    // Open a file stream using hopen
    hFILE *hfile = hopen("./dummy_file", "r");
    if (!hfile) return 0;

    // Open a htsFile using hts_hopen
    htsFile *hts_fp = hts_hopen(hfile, "./dummy_file", "r");
    if (!hts_fp) {
        hclose(hfile); // Close hFILE only if hts_hopen fails
        return 0;
    }

    // Read SAM/BAM/CRAM header
    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {
        sam_hdr_destroy(header);
    }

    // Close the htsFile
    hts_close(hts_fp); // This will also close the underlying hFILE

    return 0;
}