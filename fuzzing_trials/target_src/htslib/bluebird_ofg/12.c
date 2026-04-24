#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for file paths
    if (size < 3) {
        return 0;
    }

    // Create temporary filenames for testing
    char tmpl1[] = "/tmp/fuzzfile1XXXXXX";
    char tmpl2[] = "/tmp/fuzzfile2XXXXXX";
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);

    // Write the fuzz data to the first temporary file
    FILE *file1 = fdopen(fd1, "wb");
    if (file1 == NULL) {
        return 0;
    }
    fwrite(data, 1, size / 2, file1);
    fclose(file1);

    // Write the remaining fuzz data to the second temporary file
    FILE *file2 = fdopen(fd2, "wb");
    if (file2 == NULL) {
        return 0;
    }
    fwrite(data + size / 2, 1, size - (size / 2), file2);
    fclose(file2);

    // Open the first file as an htsFile
    htsFile *hts_fp = hts_open(tmpl1, "r");
    if (!hts_fp) {
        return 0;
    }

    // Call the function-under-test
    hts_idx_t *idx = sam_index_load3(hts_fp, tmpl1, tmpl2, 0);

    // Clean up
    if (idx) {
        hts_idx_destroy(idx);
    }
    hts_close(hts_fp);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_12(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
