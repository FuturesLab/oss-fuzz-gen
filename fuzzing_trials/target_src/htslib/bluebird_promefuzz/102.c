#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/hts.h"
#include "htslib/hfile.h"
#include "htslib/sam.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    write_dummy_file(Data, Size);

    // Open a file stream using hopen
    hFILE *hfile = hopen("./dummy_file", "r");
    if (!hfile) {
        return 0;
    }

    // Open a htsFile using hts_hopen
    htsFile *hts_fp = hts_hopen(hfile, "./dummy_file", "r");
    if (!hts_fp) {
        hclose(hfile); // Close hFILE only if hts_hopen fails
        
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hclose to hpeek
        sam_hdr_t* ret_sam_hdr_read_okgba = sam_hdr_read(hts_fp);
        if (ret_sam_hdr_read_okgba == NULL){
        	return 0;
        }

        ssize_t ret_hpeek_exnym = hpeek(hfile, (void *)hts_fp, BAM_CBACK);

        // End mutation: Producer.APPEND_MUTATOR

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