#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For mkstemp, write, close
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Ensure there's enough data to create filenames
    }

    // Create temporary file names
    char tmpl1[] = "/tmp/fuzzfileXXXXXX";
    char tmpl2[] = "/tmp/fuzzfileXXXXXX";

    // Create temporary files
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);

    if (fd1 == -1 || fd2 == -1) {
        return 0; // Failed to create temporary files
    }

    // Write the fuzz data to the first temporary file
    write(fd1, data, size);
    close(fd1);

    // Use the second temporary file as an index file
    close(fd2);

    // Call the function-under-test
    hts_idx_t *idx = hts_idx_load3(tmpl1, tmpl2, HTS_FMT_CSI, 0);

    // Clean up
    if (idx != NULL) {
        hts_idx_destroy(idx);
    }
    remove(tmpl1);
    remove(tmpl2);

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

    LLVMFuzzerTestOneInput_41(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
