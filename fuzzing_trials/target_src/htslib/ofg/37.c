#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function signature
ssize_t sam_parse_cigar(const char *cigar, char **op, uint32_t **len, size_t *n);

// Fuzzer entry point
int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the cigar string and ensure null termination
    char *cigar = (char *)malloc(size + 1);
    if (cigar == NULL) {
        return 0;
    }
    memcpy(cigar, data, size);
    cigar[size] = '\0';

    // Initialize variables for the function parameters
    char *op = NULL;
    uint32_t *len = NULL;
    size_t n = 0;

    // Call the function-under-test
    ssize_t result = sam_parse_cigar(cigar, &op, &len, &n);

    // Free allocated memory
    free(cigar);
    free(op);
    free(len);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_37(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
