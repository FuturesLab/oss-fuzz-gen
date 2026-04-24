#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>  // Include the necessary header for bam1_t

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Initialize two bam1_t structures
    bam1_t *dest = bam_init1();
    bam1_t *src = bam_init1();

    if (dest == NULL || src == NULL) {
        if (dest != NULL) bam_destroy1(dest);
        if (src != NULL) bam_destroy1(src);
        return 0;
    }

    // Simulate some data for the source bam1_t
    if (size > 0) {
        // Ensure the data fits into the bam1_t structure
        // Allocate enough space for src->data
        if (src->m_data < size) {
            uint8_t *new_data = realloc(src->data, size);
            if (new_data == NULL) {
                bam_destroy1(dest);
                bam_destroy1(src);
                return 0;
            }
            src->data = new_data;
            src->m_data = size;
        }
        memcpy(src->data, data, size);
        src->l_data = size;
    }

    // Call the function-under-test
    bam1_t *result = bam_copy1(dest, src);

    // Check if the copy was successful
    if (result != NULL && dest->l_data == src->l_data && memcmp(dest->data, src->data, src->l_data) == 0) {
        // Successfully copied
        printf("Copy successful\n");
    } else {
        printf("Copy failed\n");
    }

    // Clean up
    bam_destroy1(dest);
    bam_destroy1(src);

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

    LLVMFuzzerTestOneInput_190(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
