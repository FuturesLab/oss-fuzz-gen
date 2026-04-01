extern "C" {
    #include <tiffio.h>
    #include <unistd.h>  // For close() and write()
    #include <sys/types.h>  // For ssize_t
    #include <fcntl.h>  // For mkstemp()
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
}

// Dummy implementations of the callback functions
tsize_t dummyReadWriteProc(thandle_t, tdata_t, tsize_t) {
    return 0;
}

toff_t dummySeekProc_40(thandle_t, toff_t, int) {
    return 0;
}

int dummyCloseProc_40(thandle_t) {
    return 0;
}

toff_t dummySizeProc_40(thandle_t) {
    return 0;
}

int dummyMapFileProc_40(thandle_t, tdata_t*, toff_t*) {
    return 0;
}

void dummyUnmapFileProc_40(thandle_t, tdata_t, toff_t) {
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Create temporary filenames for the TIFFClientOpen function
    char filename[] = "/tmp/fuzz_tiff_XXXXXX";
    char mode[] = "r";

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor as TIFFClientOpen will open it again
    close(fd);

    // Call the TIFFClientOpen function with dummy callbacks
    TIFF *tiff = TIFFClientOpen(filename, mode, nullptr, dummyReadWriteProc, dummyReadWriteProc,
                                dummySeekProc_40, dummyCloseProc_40, dummySizeProc_40,
                                dummyMapFileProc_40, dummyUnmapFileProc_40);

    // If TIFFClientOpen returns a valid TIFF pointer, close it
    if (tiff) {
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(filename);

    return 0;
}