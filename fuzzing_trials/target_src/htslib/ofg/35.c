#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function signature
ssize_t sam_parse_cigar(const char *cigar_str, char **end, uint32_t **cigar, size_t *n_cigar);

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the cigar string and ensure null-termination
    char *cigar_str = (char *)malloc(size + 1);
    if (cigar_str == NULL) {
        return 0;
    }
    memcpy(cigar_str, data, size);
    cigar_str[size] = '\0';

    // Initialize variables for the function parameters
    char *end = NULL;
    uint32_t *cigar = NULL;
    size_t n_cigar = 0;

    // Call the function-under-test
    ssize_t result = sam_parse_cigar(cigar_str, &end, &cigar, &n_cigar);

    // Free allocated memory
    free(cigar_str);
    free(cigar);

    return 0;
}