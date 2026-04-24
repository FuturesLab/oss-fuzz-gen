#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close() and unlink()
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include <htslib/hts_log.h>
#include <htslib/hts_os.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Prepare a temporary filename for the index file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit the fuzzing iteration
    }
    close(fd);

    // Prepare a temporary filename for the data file
    char tmpl_data[] = "/tmp/fuzzdataXXXXXX";
    int fd_data = mkstemp(tmpl_data);
    if (fd_data == -1) {
        unlink(tmpl); // Cleanup the index file
        return 0; // If file creation fails, exit the fuzzing iteration
    }
    close(fd_data);

    // Write the fuzz data to the data file
    FILE *data_file = fopen(tmpl_data, "wb");
    if (data_file == NULL) {
        unlink(tmpl);
        unlink(tmpl_data);
        return 0;
    }
    fwrite(data, 1, size, data_file);
    fclose(data_file);

    // Create a dummy hts_idx_t object
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 14, 5); // Corrected the function call with required arguments

    // Call the function-under-test
    int result = hts_idx_save_as(idx, tmpl, tmpl_data, HTS_FMT_CSI);

    // Cleanup
    hts_idx_destroy(idx);
    unlink(tmpl);
    unlink(tmpl_data);

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

    LLVMFuzzerTestOneInput_145(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
