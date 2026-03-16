#include "tiffio.h"
#include "cstdint"
#include "cstdlib"
#include "cstring"
#include <unistd.h>  // Include for close() function

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
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
    int ret_TIFFVGetField_upros = TIFFVSetField(tiff, TIFF_VARIABLE, NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_TIFFVGetField_upros < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFVSetField to TIFFComputeTile
    uint64_t ret_TIFFScanlineSize64_oxdbd = TIFFScanlineSize64(tiff);
    if (ret_TIFFScanlineSize64_oxdbd < 0){
    	return 0;
    }
    int ret_TIFFGetMode_sticn = TIFFGetMode(tiff);
    if (ret_TIFFGetMode_sticn < 0){
    	return 0;
    }
    double pkwcdxba = 1;
    TIFFSwabDouble(&pkwcdxba);
    int ret_TIFFIsCODECConfigured_wlumf = TIFFIsCODECConfigured(1);
    if (ret_TIFFIsCODECConfigured_wlumf < 0){
    	return 0;
    }

    uint32_t ret_TIFFComputeTile_ohgte = TIFFComputeTile(tiff, (uint32_t )ret_TIFFVGetField_upros, (uint32_t )ret_TIFFGetMode_sticn, (uint32_t )pkwcdxba, (uint16_t )ret_TIFFIsCODECConfigured_wlumf);
    if (ret_TIFFComputeTile_ohgte < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    const TIFFField *field = TIFFFieldWithName(tiff, fieldName);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFFieldWithName to TIFFSetSubDirectory

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFCurrentDirOffset with TIFFStripSize64
    uint64_t ret_TIFFCurrentDirOffset_uamnh = TIFFStripSize64(tiff);
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