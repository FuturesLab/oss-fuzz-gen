#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <tiffio.h>

extern "C" {

static tsize_t dummyReadProc(thandle_t, tdata_t, tsize_t) {
    return 0;
}

static tsize_t dummyWriteProc(thandle_t, tdata_t, tsize_t) {
    return 0;
}

static toff_t dummySeekProc(thandle_t, toff_t, int) {
    return 0;
}

static int dummyCloseProc(thandle_t) {
    return 0;
}

static toff_t dummySizeProc(thandle_t) {
    return 0;
}

static int dummyMapFileProc(thandle_t, tdata_t*, toff_t*) {
    return 0;
}

static void dummyUnmapFileProc(thandle_t, tdata_t, toff_t) {
}

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Create a temporary filename
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor as it's no longer needed
    close(fd);

    // Open the TIFF file using the TIFFClientOpen function
    TIFF *tiff = TIFFClientOpen(tmpl, "r", nullptr, dummyReadProc, dummyWriteProc,
                                dummySeekProc, dummyCloseProc, dummySizeProc,
                                dummyMapFileProc, dummyUnmapFileProc);

    // If the TIFF file was successfully opened, close it
    if (tiff) {
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}

}