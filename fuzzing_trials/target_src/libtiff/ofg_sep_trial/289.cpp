#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for 'close'
#include <tiffio.h>

extern "C" {

static tmsize_t dummyReadWriteProc(thandle_t, void*, tmsize_t) {
    return 0;
}

static tmsize_t dummyReadWriteProc2(thandle_t, void*, tmsize_t) {
    return 0;
}

static toff_t dummySeekProc_289(thandle_t, toff_t, int) {
    return 0;
}

static int dummyCloseProc_289(thandle_t) {
    return 0;
}

static toff_t dummySizeProc_289(thandle_t) {
    return 0;
}

static int dummyMapFileProc_289(thandle_t, void**, toff_t*) {
    return 0;
}

static void dummyUnmapFileProc_289(thandle_t, void*, toff_t) {
}

int LLVMFuzzerTestOneInput_289(const uint8_t *data, size_t size) {
    // Create a temporary file to use as input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file using the provided TIFFClientOpenExt function
    TIFF *tiff = TIFFClientOpen(
        tmpl, "r", (thandle_t)(intptr_t)fd,  // Cast to intptr_t to avoid warning
        dummyReadWriteProc, dummyReadWriteProc2,
        dummySeekProc_289, dummyCloseProc_289,
        dummySizeProc_289, dummyMapFileProc_289,
        dummyUnmapFileProc_289
    );

    // If successfully opened, close the TIFF file
    if (tiff) {
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}

}