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

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of tjLoadImage
    int pxakmwbd = size;
    unsigned char *image = tjLoadImage(tmpl, &width, 1, &height, &pxakmwbd, flags);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (image != NULL) {
        tjFree(image);
    }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjFree to tjEncodeYUV
        tjhandle ret_tj3Init_tdgnu = tj3Init(TJ_BGR);
        int kgatqtdk = size;
        tjscalingfactor* ret_tjGetScalingFactors_bkjit = tjGetScalingFactors(&kgatqtdk);
        if (ret_tjGetScalingFactors_bkjit == NULL){
        	return 0;
        }
        unsigned char* ret_tjAlloc_nnlyl = tjAlloc(0);
        if (ret_tjAlloc_nnlyl == NULL){
        	return 0;
        }
        int snnfksfg = -1;
        tjscalingfactor* ret_tjGetScalingFactors_mbybn = tjGetScalingFactors(&snnfksfg);
        if (ret_tjGetScalingFactors_mbybn == NULL){
        	return 0;
        }

        int ret_tjEncodeYUV_iralf = tjEncodeYUV(ret_tj3Init_tdgnu, image, TJ_NUMSAMP, kgatqtdk, TJXOPT_GRAY, height, ret_tjAlloc_nnlyl, snnfksfg, TJXOPT_CROP);
        if (ret_tjEncodeYUV_iralf < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl); // Remove the temporary file

    return 0;
}