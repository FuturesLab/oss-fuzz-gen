#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Call the function-under-test
    bam1_t *bam = bam_init1();

    // Check if bam is not NULL
    if (bam != NULL) {
        // Perform some operations on the bam1_t object if needed
        // For now, we will just print a message
        printf("bam1_t object initialized.\n");

        // Free the bam1_t object
        bam_destroy1(bam);
    } else {
        printf("Failed to initialize bam1_t object.\n");
    }

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

    LLVMFuzzerTestOneInput_66(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
