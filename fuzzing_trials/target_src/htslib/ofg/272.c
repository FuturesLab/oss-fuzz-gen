#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Added for close() and unlink()
#include <htslib/hts.h>
#include <htslib/hts_defs.h>

int LLVMFuzzerTestOneInput_272(const uint8_t *data, size_t size) {
    char tmpl1[] = "/tmp/fuzzfile1XXXXXX";
    char tmpl2[] = "/tmp/fuzzfile2XXXXXX";
    int fd1, fd2;
    FILE *file1, *file2;
    hts_idx_t *index = NULL;

    if (size < 2) {
        return 0;
    }

    fd1 = mkstemp(tmpl1);
    if (fd1 == -1) {
        return 0;
    }

    fd2 = mkstemp(tmpl2);
    if (fd2 == -1) {
        close(fd1);
        unlink(tmpl1);
        return 0;
    }

    file1 = fdopen(fd1, "wb");
    file2 = fdopen(fd2, "wb");

    if (file1 == NULL || file2 == NULL) {
        close(fd1);
        close(fd2);
        unlink(tmpl1);
        unlink(tmpl2);
        return 0;
    }

    fwrite(data, 1, size / 2, file1);
    fwrite(data + size / 2, 1, size - size / 2, file2);

    fclose(file1);
    fclose(file2);

    index = hts_idx_load2(tmpl1, tmpl2);

    if (index != NULL) {
        hts_idx_destroy(index);
    }

    unlink(tmpl1);
    unlink(tmpl2);

    return 0;
}