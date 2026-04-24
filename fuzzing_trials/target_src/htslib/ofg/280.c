#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>  // Include the necessary header for bam1_t

int LLVMFuzzerTestOneInput_280(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a bam1_t structure
    if (size < sizeof(bam1_t)) {
        return 0;
    }

    // Allocate memory for bam1_t and initialize it
    bam1_t *bam_record = (bam1_t *)malloc(sizeof(bam1_t));
    if (bam_record == NULL) {
        return 0;
    }

    // Initialize the bam1_t structure with the provided data
    // Note: This is a simplistic initialization and may need adjustments
    // depending on the actual structure and requirements of bam1_t
    bam_record->data = (uint8_t *)data;
    bam_record->l_data = size;

    // Call the function-under-test
    uint8_t *result = bam_aux_first(bam_record);

    // For fuzzing purposes, we don't need to do anything with the result
    // but we could print it or perform checks if needed
    if (result != NULL) {
        printf("Auxiliary data found: %p\n", (void *)result);
    }

    // Free the allocated memory
    free(bam_record);

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

    LLVMFuzzerTestOneInput_280(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
