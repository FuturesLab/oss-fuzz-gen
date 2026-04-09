#include <stdint.h>
#include <stddef.h>
#include <htslib/sam.h> // Include the necessary header for bam_cigar2rlen

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an integer and at least one uint32_t
    if (size < sizeof(int) + sizeof(uint32_t)) {
        return 0;
    }

    // Extract an integer from the data
    int n_cigar = *((int *)data);

    // Ensure n_cigar is a positive number to avoid undefined behavior
    if (n_cigar <= 0) {
        return 0;
    }

    // Calculate the number of uint32_t elements we can safely extract
    size_t num_cigar_ops = (size - sizeof(int)) / sizeof(uint32_t);

    // Ensure we have at least n_cigar uint32_t elements
    if (num_cigar_ops < (size_t)n_cigar) {
        return 0;
    }

    // Extract the uint32_t array from the data
    const uint32_t *cigar = (const uint32_t *)(data + sizeof(int));

    // Call the function-under-test
    hts_pos_t result = bam_cigar2rlen(n_cigar, cigar);

    (void)result; // Suppress unused variable warning

    return 0;
}