#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    htsFile *file = NULL;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    FILE *fp = fdopen(fd, "wb");
    if (fp == NULL) {
        close(fd);
        return 0;
    }

    if (fwrite(data, 1, size, fp) != size) {
        fclose(fp);
        return 0;
    }

    fclose(fp);

    file = hts_open(tmpl, "r");
    if (file == NULL) {
        return 0;
    }

    hts_flush(file);

    hts_close(file);
    unlink(tmpl);

    return 0;
}