#include <tiffio.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>  // For mkstemp, write, and close
#include <fcntl.h>   // For file control options
#include <cstdint>   // For uint8_t
#include <cstdlib>   // For remove

extern "C" {

TIFF *TIFFClientOpenExt(const char *, const char *, thandle_t, TIFFReadWriteProc, TIFFReadWriteProc, TIFFSeekProc, TIFFCloseProc, TIFFSizeProc, TIFFMapFileProc, TIFFUnmapFileProc, TIFFOpenOptions *);

static tmsize_t readProc(thandle_t, void *buf, tmsize_t size) {
    memset(buf, 0, size);
    return size;
}

static tmsize_t writeProc(thandle_t, void *buf, tmsize_t size) {
    return size;
}

static toff_t seekProc(thandle_t, toff_t off, int whence) {
    return off;
}

static int closeProc(thandle_t) {
    return 0;
}

static toff_t sizeProc(thandle_t) {
    return 1024;
}

static int mapProc(thandle_t, void **base, toff_t *size) {
    *base = nullptr;
    *size = 0;
    return 0;
}

static void unmapProc(thandle_t, void *base, toff_t size) {
}

int LLVMFuzzerTestOneInput_291(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    const char *mode = "r";
    char filename[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    TIFF *tif = TIFFClientOpenExt(filename, mode, (thandle_t)(intptr_t)fd, readProc, writeProc, seekProc, closeProc, sizeProc, mapProc, unmapProc, options);

    if (tif) {
        TIFFClose(tif);
    }

    TIFFOpenOptionsFree(options);
    remove(filename);

    return 0;
}

}