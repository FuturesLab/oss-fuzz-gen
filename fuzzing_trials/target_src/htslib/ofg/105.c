#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h> // Include the necessary header for bam1_t

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure there's enough data for the tag and int64_t value
    if (size < 3) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t *bam = bam_init1();
    if (bam == NULL) {
        return 0;
    }

    // Extract a two-character tag from the input data
    char tag[3];
    memcpy(tag, data, 2);
    tag[2] = '\0'; // Null-terminate the tag string

    // Extract an int64_t value from the input data
    int64_t value;
    memcpy(&value, data + 2, sizeof(int64_t));

    // Call the function-under-test
    bam_aux_update_int(bam, tag, value);

    // Clean up
    bam_destroy1(bam);

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

    LLVMFuzzerTestOneInput_105(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
