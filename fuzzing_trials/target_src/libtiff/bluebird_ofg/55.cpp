#include "tiffio.h"
#include "cstdint"
#include "cstdlib"
#include "cstring"
#include <unistd.h>  // Include for close() function

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    } // Ensure there's at least some data

    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "rm");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Use a non-null string for the field name
    const char *fieldName = "SampleFieldName";

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFOpen to TIFFVGetField


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFVGetField with TIFFVSetField

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFVSetField with TIFFVGetFieldDefaulted
    int ret_TIFFVGetField_upros = TIFFVGetFieldDefaulted(tiff, TIFF_VARIABLE, NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_TIFFVGetField_upros < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    const TIFFField *field = TIFFFieldWithName(tiff, fieldName);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFFieldWithName to TIFFSetSubDirectory

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFCurrentDirOffset with TIFFRasterScanlineSize64
    uint64_t ret_TIFFCurrentDirOffset_uamnh = TIFFRasterScanlineSize64(tiff);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_TIFFCurrentDirOffset_uamnh < 0){
    	return 0;
    }

    int ret_TIFFSetSubDirectory_jmjpr = TIFFSetSubDirectory(tiff, ret_TIFFCurrentDirOffset_uamnh);
    if (ret_TIFFSetSubDirectory_jmjpr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}