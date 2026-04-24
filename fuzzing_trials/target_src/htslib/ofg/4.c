#include <stdint.h>
#include <stddef.h>
#include <htslib/sam.h> // Ensure that the htslib library is installed and included

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure that the size is appropriate for the input parameters
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize the parameters for bam_cigar2qlen
    int n_cigar = (int)(size / sizeof(uint32_t)); // Number of cigar operations

    // Cast the data to a uint32_t pointer
    const uint32_t *cigar = (const uint32_t *)data;

    // Call the function-under-test
    hts_pos_t qlen = bam_cigar2qlen(n_cigar, cigar);

    // Use the result to avoid compiler optimizations that remove the function call
    (void)qlen;

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

    LLVMFuzzerTestOneInput_4(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
