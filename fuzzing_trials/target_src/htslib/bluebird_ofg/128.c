#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htslib/sam.h" // Correct header file for bam1_t and bam_aux_append

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    if (size < 8) { // Ensure there is enough data for the parameters and auxiliary data
        return 0; // Handle insufficient input size
    }

    bam1_t *bam = bam_init1(); // Properly initialize bam1_t structure
    if (!bam) {
        return 0; // Handle memory allocation failure
    }

    // Use the first byte as the character
    char aux_char = (char)data[0];

    // Use the second byte as the integer
    int aux_int = (int)data[1];

    // Use the next 3 bytes as a string for the tag
    char tag[4];
    memcpy(tag, data + 2, 3);
    tag[3] = '\0'; // Null-terminate the string

    // Use the next 4 bytes as the auxiliary data
    const uint8_t *aux_data = data + 5;
    size_t aux_data_size = size - 5;

    // Ensure aux_data_size is sufficient for the expected data type
    if (aux_data_size < 4) { // Ensure there is enough data for an integer
        bam_destroy1(bam); // Clean up before returning
        return 0;
    }

    // Call the function-under-test
    int result = bam_aux_append(bam, tag, aux_char, aux_data, 4); // Correct parameter order and size

    bam_destroy1(bam); // Clean up after usage

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_128(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
