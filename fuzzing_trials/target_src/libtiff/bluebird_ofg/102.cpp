#include "cstdint"
#include "cstdlib"
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor as TIFFOpen will open it again
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFCreateGPSDirectory with TIFFReadDirectory
    TIFFReadDirectory(tiff);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Close the TIFF file

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFReadDirectory to TIFFGetStrileOffsetWithErr
    int ret_TIFFIsCODECConfigured_vsewk = TIFFIsCODECConfigured(CIELABTORGB_TABLE_RANGE);
    if (ret_TIFFIsCODECConfigured_vsewk < 0){
    	return 0;
    }
    uint32_t ret_TIFFCurrentStrip_sjgyy = TIFFCurrentStrip(tiff);
    if (ret_TIFFCurrentStrip_sjgyy < 0){
    	return 0;
    }

    uint64_t ret_TIFFGetStrileOffsetWithErr_lchne = TIFFGetStrileOffsetWithErr(tiff, (uint32_t )ret_TIFFIsCODECConfigured_vsewk, (int *)&ret_TIFFCurrentStrip_sjgyy);
    if (ret_TIFFGetStrileOffsetWithErr_lchne < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    TIFFClose(tiff);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}