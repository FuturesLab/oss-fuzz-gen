#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/src/htslib/htslib/sam.h" // Correct path for bam1_t and related functions

// Function-under-test
int bam_aux_update_float(bam1_t *b, const char *tag, float value);

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the required parameters
    if (size < sizeof(float) + 2) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t b;
    memset(&b, 0, sizeof(bam1_t)); // Initialize all fields to zero

    // Extract the float value from the input data
    float value;
    memcpy(&value, data, sizeof(float));

    // Extract the tag from the input data
    char tag[3] = {0}; // 2 characters for the tag and 1 for the null terminator
    memcpy(tag, data + sizeof(float), 2);

    // Call the function-under-test
    int result = bam_aux_update_float(&b, tag, value);

    // Optionally, you can print the result or perform additional checks
    // printf("Result: %d\n", result);

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

    LLVMFuzzerTestOneInput_140(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
