#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize all parameters
    if (size < sizeof(uint32_t) * 3 + 3 * sizeof(hts_pos_t) + 3 * sizeof(size_t) + 2 * sizeof(char)) {
        return 0;
    }

    // Initialize parameters for bam_set1
    bam1_t *b = bam_init1();
    if (!b) {
        return 0; // Ensure bam1_t is initialized successfully
    }

    size_t offset = 0;
    
    // Ensure qname is null-terminated within the bounds of the data
    size_t max_qname_len = size - offset;
    const char *qname = (const char *)data;
    size_t qname_len = strnlen(qname, max_qname_len);
    
    if (qname_len == max_qname_len) {
        bam_destroy1(b);
        return 0; // qname is not null-terminated within the available data
    }
    
    offset += qname_len + 1; // Move offset past qname

    if (offset + sizeof(uint16_t) + sizeof(int32_t) + sizeof(hts_pos_t) + sizeof(uint8_t) + sizeof(size_t) > size) {
        bam_destroy1(b);
        return 0;
    }

    uint16_t flag = *(uint16_t *)(data + offset);
    offset += sizeof(uint16_t);
    int32_t tid = *(int32_t *)(data + offset);
    offset += sizeof(int32_t);
    hts_pos_t pos = *(hts_pos_t *)(data + offset);
    offset += sizeof(hts_pos_t);
    uint8_t mapq = *(uint8_t *)(data + offset);
    offset += sizeof(uint8_t);
    size_t n_cigar = *(size_t *)(data + offset);
    offset += sizeof(size_t);

    if (offset + n_cigar * sizeof(uint32_t) + sizeof(int32_t) + 2 * sizeof(hts_pos_t) + sizeof(size_t) > size) {
        bam_destroy1(b);
        return 0;
    }

    const uint32_t *cigar = (const uint32_t *)(data + offset);
    offset += n_cigar * sizeof(uint32_t);
    int32_t mtid = *(int32_t *)(data + offset);
    offset += sizeof(int32_t);
    hts_pos_t mpos = *(hts_pos_t *)(data + offset);
    offset += sizeof(hts_pos_t);
    hts_pos_t isize = *(hts_pos_t *)(data + offset);
    offset += sizeof(hts_pos_t);
    size_t l_seq = *(size_t *)(data + offset);
    offset += sizeof(size_t);

    if (offset + l_seq + l_seq + sizeof(size_t) > size) {
        bam_destroy1(b);
        return 0;
    }

    const char *seq = (const char *)(data + offset);
    offset += l_seq;
    const char *qual = (const char *)(data + offset);
    offset += l_seq;
    size_t l_aux = *(size_t *)(data + offset);
    offset += sizeof(size_t);

    if (offset + l_aux > size) {
        bam_destroy1(b);
        return 0;
    }

    // Call the function-under-test
    bam_set1(b, size, qname, flag, tid, pos, mapq, n_cigar, cigar, mtid, mpos, isize, l_seq, seq, qual, l_aux);

    // Clean up
    bam_destroy1(b);

    return 0;
}