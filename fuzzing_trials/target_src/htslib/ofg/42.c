#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    char tmpl1[] = "/tmp/fuzzfile1XXXXXX";
    char tmpl2[] = "/tmp/fuzzfile2XXXXXX";
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);

    if (fd1 == -1 || fd2 == -1) {
        return 0;
    }

    // Write the fuzz data to the first temporary file
    if (write(fd1, data, size) != size) {
        close(fd1);
        close(fd2);
        return 0;
    }

    // Close the file descriptors
    close(fd1);
    close(fd2);

    // Call the function-under-test
    hts_idx_t *index = hts_idx_load3(tmpl1, tmpl2, HTS_FMT_CSI, HTS_IDX_SAVE_REMOTE);

    // Clean up
    if (index != NULL) {
        hts_idx_destroy(index);
    }

    // Remove the temporary files
    unlink(tmpl1);
    unlink(tmpl2);

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

    LLVMFuzzerTestOneInput_42(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
