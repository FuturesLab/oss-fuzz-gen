#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>  // Ensure you have the HTSlib library available

int LLVMFuzzerTestOneInput_286(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    bam1_t *b = bam_init1();
    uint8_t *aux = NULL;

    if (b == NULL || size < 1) {
        bam_destroy1(b);
        return 0;
    }

    // Allocate memory for auxiliary data
    aux = (uint8_t *)malloc(size);
    if (aux == NULL) {
        bam_destroy1(b);
        return 0;
    }

    // Copy data to auxiliary data
    memcpy(aux, data, size);

    // Call the function-under-test
    uint8_t *result = bam_aux_remove(b, aux);

    // Clean up
    bam_destroy1(b);
    free(aux);

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

    LLVMFuzzerTestOneInput_286(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
