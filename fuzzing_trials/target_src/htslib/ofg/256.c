#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>
#include <htslib/hts.h> // Ensure the correct header file for bam_plp_t

// Remove the extern "C" as this is C code, not C++
int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    // Declare and initialize a bam_plp_t variable
    bam_plp_t plp = bam_plp_init(NULL, NULL);

    if (plp == NULL) {
        // If initialization fails, exit early
        return 0;
    }

    // Check if data is not NULL and size is greater than 0
    if (data != NULL && size > 0) {
        // Utilize the data in some meaningful way
        // For example, you could process the data here
        // This is a placeholder for actual data processing
    }

    // Call the function-under-test
    bam_plp_reset(plp);

    // Clean up by destroying the bam_plp_t instance
    bam_plp_destroy(plp);

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

    LLVMFuzzerTestOneInput_256(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
