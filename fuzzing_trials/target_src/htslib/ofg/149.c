#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Initialize parameters for bam_set1
    bam1_t bam;
    bam1_t *b = &bam;
    size_t l_data = size > 0 ? size : 1; // Ensure size is not zero
    const char *qname = "query_name";
    uint16_t flag = 1;
    int32_t tid = 0;
    hts_pos_t pos = 0;
    uint8_t mapq = 255;
    size_t n_cigar = 1;
    uint32_t cigar[1] = {0};
    int32_t mtid = 0;
    hts_pos_t mpos = 0;
    hts_pos_t isize = 0;
    size_t l_seq = size > 0 ? size : 1; // Ensure size is not zero
    const char *seq = "ACTG";
    const char *qual = "*";
    size_t l_aux = size > 0 ? size : 1; // Ensure size is not zero

    // Call the function under test
    int result = bam_set1(b, l_data, qname, flag, tid, pos, mapq, n_cigar, cigar, mtid, mpos, isize, l_seq, seq, qual, l_aux);

    // Return 0 to indicate the function has been called
    return 0;
}