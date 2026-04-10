#include <stdint.h>
#include <stddef.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    int n_cigar = 0;
    const uint32_t *cigar = NULL;

    if (size >= sizeof(int) + sizeof(uint32_t)) {
        n_cigar = *((int *)data);
        cigar = (const uint32_t *)(data + sizeof(int));

        // Ensure n_cigar is within a reasonable range to prevent excessive memory access
        if (n_cigar > 0 && n_cigar <= (size - sizeof(int)) / sizeof(uint32_t)) {
            hts_pos_t result = bam_cigar2rlen(n_cigar, cigar);
        }
    }

    return 0;
}