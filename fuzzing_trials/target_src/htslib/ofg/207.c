#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>

// Fuzzing harness for hts_itr_destroy
int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    // Initialize a hts_itr_t pointer
    hts_itr_t *itr = (hts_itr_t *)malloc(sizeof(hts_itr_t));

    // Ensure the pointer is not NULL
    if (itr == NULL) {
        return 0;
    }

    // Populate the hts_itr_t structure with some data
    // Here we are using the input data to fill the structure
    // This is a simple example; in practice, you might need to
    // set specific fields based on the expected usage of the structure
    if (size >= sizeof(hts_itr_t)) {
        *itr = *(hts_itr_t *)data;
    } else {
        // If the input data is smaller than the size of hts_itr_t,
        // just fill what we can and zero the rest
        memcpy(itr, data, size);
        memset(((uint8_t *)itr) + size, 0, sizeof(hts_itr_t) - size);
    }

    // Call the function-under-test
    hts_itr_destroy(itr);

    // Free the allocated memory
    // Note: hts_itr_destroy should handle freeing internal resources,
    // so we only free the outer structure here
    free(itr);

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

    LLVMFuzzerTestOneInput_207(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
