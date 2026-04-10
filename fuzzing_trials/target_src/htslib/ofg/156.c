#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h> // Ensure htslib is installed and available

// Function-under-test
ssize_t bam_parse_cigar(const char *cigar_str, char **end, bam1_t *b);

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Allocate memory for bam1_t
    bam1_t *b = bam_init1();
    if (b == NULL) return 0;

    // Copy the data to a null-terminated string
    char *cigar_str = (char *)malloc(size + 1);
    if (cigar_str == NULL) {
        bam_destroy1(b);
        return 0;
    }
    memcpy(cigar_str, data, size);
    cigar_str[size] = '\0';

    // Prepare the end pointer
    char *end = NULL;

    // Call the function-under-test
    bam_parse_cigar(cigar_str, &end, b);

    // Clean up
    free(cigar_str);
    bam_destroy1(b);

    return 0;
}