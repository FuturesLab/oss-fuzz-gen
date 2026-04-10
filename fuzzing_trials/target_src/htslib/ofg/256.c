#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

// Define bam_seq4_set macro if it's not available
#ifndef bam_seq4_set
#define bam_seq4_set(s, i, b) ((s)[(i)>>1] |= (b)<<((~(i)&1)<<2))
#endif

int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    if (size < sizeof(bam_hdr_t) + sizeof(bam1_t) + sizeof(kstring_t)) {
        return 0;
    }

    // Initialize bam_hdr_t
    bam_hdr_t *hdr = (bam_hdr_t *)malloc(sizeof(bam_hdr_t));
    if (!hdr) return 0;
    hdr->n_targets = 1;
    hdr->target_len = (uint32_t *)malloc(sizeof(uint32_t));
    hdr->target_name = (char **)malloc(sizeof(char *));
    hdr->target_name[0] = strdup("chr1");
    hdr->target_len[0] = 1000;

    // Initialize bam1_t
    bam1_t *b = bam_init1();
    if (!b) {
        free(hdr->target_name[0]);
        free(hdr->target_name);
        free(hdr->target_len);
        free(hdr);
        return 0;
    }

    // Use input data to fill bam1_t
    if (size > 0) {
        b->core.tid = data[0] % hdr->n_targets;
    }
    if (size > 1) {
        b->core.pos = data[1] % hdr->target_len[0];
    }
    if (size > 2) {
        b->core.qual = data[2];
    }
    b->core.l_qname = 5;
    b->core.flag = 0;
    b->core.n_cigar = 1;
    b->core.l_qseq = 4;
    b->core.mtid = -1;
    b->core.mpos = -1;
    b->core.isize = 0;

    uint8_t *qname = (uint8_t *)malloc(b->core.l_qname);
    strcpy((char *)qname, "read");
    b->data = qname;

    uint32_t *cigar = (uint32_t *)malloc(sizeof(uint32_t));
    cigar[0] = bam_cigar_gen(4, BAM_CMATCH);
    b->data = (uint8_t *)realloc(b->data, b->core.l_qname + sizeof(uint32_t));
    memcpy(b->data + b->core.l_qname, cigar, sizeof(uint32_t));

    uint8_t *seq = (uint8_t *)malloc((b->core.l_qseq + 1) / 2);
    bam_seq4_set(seq, 0, 4);
    bam_seq4_set(seq, 1, 4);
    b->data = (uint8_t *)realloc(b->data, b->core.l_qname + sizeof(uint32_t) + (b->core.l_qseq + 1) / 2);
    memcpy(b->data + b->core.l_qname + sizeof(uint32_t), seq, (b->core.l_qseq + 1) / 2);

    uint8_t *qual = (uint8_t *)malloc(b->core.l_qseq);
    memset(qual, 30, b->core.l_qseq);
    b->data = (uint8_t *)realloc(b->data, b->core.l_qname + sizeof(uint32_t) + (b->core.l_qseq + 1) / 2 + b->core.l_qseq);
    memcpy(b->data + b->core.l_qname + sizeof(uint32_t) + (b->core.l_qseq + 1) / 2, qual, b->core.l_qseq);

    // Initialize kstring_t
    kstring_t str;
    str.l = 0;
    str.m = 0;
    str.s = NULL;

    // Call the function-under-test
    sam_format1(hdr, b, &str);

    // Clean up
    free(hdr->target_name[0]);
    free(hdr->target_name);
    free(hdr->target_len);
    free(hdr);
    bam_destroy1(b);
    free(seq);
    free(qual);
    free(cigar);
    free(str.s);

    return 0;
}