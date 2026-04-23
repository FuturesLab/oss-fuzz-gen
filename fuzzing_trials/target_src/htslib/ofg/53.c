#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>

// Fuzzing harness for the hts_opt_free function
int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to create a valid hts_opt structure
    if (size < sizeof(hts_opt)) {
        return 0;
    }

    // Allocate memory for hts_opt structure
    hts_opt *options = (hts_opt *)malloc(sizeof(hts_opt));
    if (options == NULL) {
        return 0;
    }

    // Initialize the hts_opt structure with data from the fuzzer
    // Note: This assumes that hts_opt has a simple structure that can be initialized this way.
    // If hts_opt has pointers or requires specific initialization, this code will need to be adjusted.
    memcpy(options, data, sizeof(hts_opt));

    // Call the function-under-test
    hts_opt_free(options);

    // Free the allocated memory for options
    free(options);

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

    LLVMFuzzerTestOneInput_53(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
