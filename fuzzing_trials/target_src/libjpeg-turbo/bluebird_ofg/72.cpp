#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "unistd.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create temp file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0; // Failed to write data
    }
    close(fd);

    // Initialize the parameters for tjLoadImage
    int width = 0;
    int height = 0;
    int subsamp = 0;
    int colorspace = 0;
    int flags = 0;

    // Call the function-under-test
    unsigned char *image = tjLoadImage(tmpl, &width, 1, &height, &subsamp, flags);

    // Clean up
    if (image != NULL) {
        tjFree(image);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjLoadImage to tj3LoadImage16
    tjhandle ret_tj3Init_yjeda = tj3Init(TJ_BGR);
    void* ret_tj3Alloc_tursd = tj3Alloc(TJFLAG_LIMITSCANS);
    if (ret_tj3Alloc_tursd == NULL){
    	return 0;
    }
    int xsaptdbk = 0;
    tjscalingfactor* ret_tjGetScalingFactors_maldi = tjGetScalingFactors(&xsaptdbk);
    if (ret_tjGetScalingFactors_maldi == NULL){
    	return 0;
    }
    tjscalingfactor* ret_tjGetScalingFactors_ssohi = tjGetScalingFactors(&subsamp);
    if (ret_tjGetScalingFactors_ssohi == NULL){
    	return 0;
    }
    int ddclsrgp = 64;
    tjscalingfactor* ret_tj3GetScalingFactors_ctcjk = tj3GetScalingFactors(&ddclsrgp);
    if (ret_tj3GetScalingFactors_ctcjk == NULL){
    	return 0;
    }

    unsigned short* ret_tj3LoadImage16_uwabc = tj3LoadImage16(ret_tj3Init_yjeda, (const char *)ret_tj3Alloc_tursd, &xsaptdbk, width, &subsamp, &ddclsrgp);
    if (ret_tj3LoadImage16_uwabc == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl); // Remove the temporary file

    return 0;
}