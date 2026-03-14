#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include this for malloc and free
#include "lcms2.h"

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cmsCreateContext
    char xjkuzmzu[1024] = "bfmzr";
    cmsContext context = cmsCreateContext(xjkuzmzu, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    cmsIOHANDLER *iohandler = NULL;

    // Ensure there is enough data to create two strings
    if (size < 2) {
        cmsDeleteContext(context);
        return 0;
    }

    // Split the input data into two parts for the file name and the mode
    size_t mid = size / 2;
    char *filename = (char *)malloc(mid + 1);
    char *mode = (char *)malloc(size - mid + 1);

    if (filename == NULL || mode == NULL) {
        free(filename);
        free(mode);
        cmsDeleteContext(context);
        return 0;
    }

    memcpy(filename, data, mid);
    filename[mid] = '\0';

    memcpy(mode, data + mid, size - mid);
    mode[size - mid] = '\0';

    // Call the function under test
    iohandler = cmsOpenIOhandlerFromFile(context, filename, mode);

    // Clean up
    if (iohandler != NULL) {
        cmsCloseIOhandler(iohandler);
    }
    free(filename);
    free(mode);
    cmsDeleteContext(context);

    return 0;
}