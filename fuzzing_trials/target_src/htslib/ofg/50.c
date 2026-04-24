#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <htslib/hts.h>
#include <htslib/bgzf.h>
#include <htslib/tbx.h>  // Include this for hts_idx_t and related functions

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Create a temporary file to use as the filename input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Initialize a dummy hts_idx_t object with the correct number of parameters
    uint64_t offset0 = 0;
    int min_shift = 14;  // Example value
    int n_lvls = 5;      // Example value
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, offset0, min_shift, n_lvls);

    // Set a non-null value for the int parameter
    int fmt = HTS_FMT_CSI;  // Use a valid format for the index

    // Call the function-under-test and check the return value
    if (hts_idx_save(idx, tmpl, fmt) < 0) {  // Corrected function call with 3 arguments
        hts_idx_destroy(idx);
        remove(tmpl);
        return 0;
    }

    // Clean up
    hts_idx_destroy(idx);
    remove(tmpl);

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

    LLVMFuzzerTestOneInput_50(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
