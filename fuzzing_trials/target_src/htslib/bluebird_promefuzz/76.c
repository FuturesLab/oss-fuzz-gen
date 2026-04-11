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

int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    write_dummy_file(Data, Size);

    // Open a file stream using hopen

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hopen
    const char pdxwzvqa[1024] = "zydvx";
    hFILE *hfile = hopen("./dummy_file", pdxwzvqa);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (!hfile) {
        return 0;
    }

    // Open a htsFile using hts_hopen
    htsFile *hts_fp = hts_hopen(hfile, "./dummy_file", "r");
    if (!hts_fp) {
        hclose(hfile); // Close hFILE only if hts_hopen fails
        return 0;
    }

    // Read SAM/BAM/CRAM header

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to hts_detect_format
    htsFormat ycxthelv;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to hseek

    off_t ret_hseek_czbps = hseek(hfile, 0, BAM_FMREVERSE);

    // End mutation: Producer.APPEND_MUTATOR

    memset(&ycxthelv, 0, sizeof(ycxthelv));

    int ret_hts_detect_format_zfwsd = hts_detect_format(hfile, &ycxthelv);
    if (ret_hts_detect_format_zfwsd < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {
        sam_hdr_destroy(header);
    }

    // Close the htsFile
    hts_close(hts_fp); // This will also close the underlying hFILE

    return 0;
}