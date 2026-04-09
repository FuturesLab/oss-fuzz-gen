#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <htslib/sam.h>  // Ensure you have the HTSlib library available

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Check if the size is sufficient for at least one uint32_t element
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Calculate the number of uint32_t elements
    int n_cigar = size / sizeof(uint32_t);

    // Cast the input data to a uint32_t pointer
    const uint32_t *cigar = (const uint32_t *)data;

    // Call the function-under-test
    hts_pos_t result = bam_cigar2qlen(n_cigar, cigar);

    // Print the result for debugging purposes (optional)
    printf("bam_cigar2qlen result: %ld\n", (long)result);

    return 0;
}