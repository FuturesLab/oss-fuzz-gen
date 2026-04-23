#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/tbx.h"
#include "/src/htslib/htslib/bgzf.h"
#include "/src/htslib/htslib/kseq.h" // Include kseq.h for sequence handling if needed

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    hts_idx_t *index;
    uint32_t meta_size;
    uint8_t *meta_data;

    // Create a temporary file to simulate a BGZF file from input data
    char tmp_filename[] = "tmp_bgzf_XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0; // Exit if temporary file creation fails
    }

    // Write input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmp_filename);
        return 0; // Exit if writing to file fails
    }
    close(fd);

    // Open the BGZF file using the temporary file
    BGZF *bgzf = bgzf_open(tmp_filename, "r");
    if (bgzf == NULL) {
        remove(tmp_filename);
        return 0; // Exit if BGZF file opening fails
    }

    // Create an index for the BGZF file
    index = tbx_index_load2(tmp_filename, NULL);
    if (index == NULL) {
        bgzf_close(bgzf);
        remove(tmp_filename);
        return 0; // Exit if index creation fails
    }

    // Call the function-under-test
    meta_data = hts_idx_get_meta(index, &meta_size);

    // Free allocated resources
    hts_idx_destroy(index);
    bgzf_close(bgzf);
    remove(tmp_filename);

    // Return 0 to indicate successful completion of the fuzzer test
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_57(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
