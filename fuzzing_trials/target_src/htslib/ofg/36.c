#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/tbx.h>  // Include the header for hts_idx_t and hts_idx_fmt
#include <htslib/bgzf.h> // Include the header for BGZF related functions

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Create a temporary file to use with the BGZF functions
    char tmp_filename[] = "/tmp/fuzz_input_XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the temporary file with BGZF
    BGZF *bgzf = bgzf_open(tmp_filename, "r");
    if (bgzf == NULL) {
        unlink(tmp_filename);
        return 0;
    }

    // Use the htslib function to create an index
    hts_idx_t *idx = tbx_index_load(tmp_filename);
    if (idx == NULL) {
        bgzf_close(bgzf);
        unlink(tmp_filename);
        return 0;
    }

    // Call the function-under-test
    int result = hts_idx_fmt(idx);

    // Clean up
    hts_idx_destroy(idx);
    bgzf_close(bgzf);
    unlink(tmp_filename);

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

    LLVMFuzzerTestOneInput_36(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
