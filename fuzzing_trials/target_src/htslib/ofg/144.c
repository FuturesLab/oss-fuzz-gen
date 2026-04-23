#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>

int dummy_function(void *data, bam1_t *b) {
    return 0; // Return a dummy value
}

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to initialize the void pointer
    if (size < sizeof(void *)) {
        return 0;
    }

    // Initialize a void pointer using the input data
    void *dummy_data = (void *)data;

    // Call the function-under-test
    bam_plp_t plp = bam_plp_init(dummy_function, dummy_data);

    // Normally, we would do something with 'plp', but for fuzzing purposes,
    // we are only interested in calling the function to see if it handles input correctly.

    // Clean up if necessary
    if (plp != NULL) {
        bam_plp_destroy(plp);
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

    LLVMFuzzerTestOneInput_144(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
