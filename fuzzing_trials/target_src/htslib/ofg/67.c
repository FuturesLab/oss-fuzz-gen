#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <htslib/sam.h>  // Include the htslib header for bam1_t

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Call the function-under-test
    bam1_t *bam_record = bam_init1();

    // Check if bam_record is not NULL
    if (bam_record != NULL) {
        // Perform operations on bam_record if needed
        // For example, you can print the memory address of bam_record
        printf("bam_record initialized at address: %p\n", (void *)bam_record);

        // Free the allocated bam_record to avoid memory leaks
        bam_destroy1(bam_record);
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

    LLVMFuzzerTestOneInput_67(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
