#include <stdint.h>
#include <stddef.h>
#include <htslib/sam.h> // Ensure that the htslib library is included

// Remove the 'extern "C"' linkage specification as it is not needed in C code
int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form at least one uint32_t element
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Calculate the number of uint32_t elements we can extract from the data
    int num_elements = size / sizeof(uint32_t);

    // Cast the data to a uint32_t pointer
    const uint32_t *cigar = (const uint32_t *)data;

    // Call the function-under-test
    hts_pos_t result = bam_cigar2qlen(num_elements, cigar);

    // Use the result in some way to prevent compiler optimizations
    (void)result;

    return 0;
}