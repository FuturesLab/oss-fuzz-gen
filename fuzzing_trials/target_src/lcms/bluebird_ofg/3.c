#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"
#include <fcntl.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for cmsIT8LoadFromFile
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        cmsDeleteContext(context);
        return 0;
    }

    // Write the data to the file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        cmsDeleteContext(context);
        return 0;
    }
    close(fd);

    // Call the function-under-test
    cmsHANDLE handle = cmsIT8LoadFromFile(context, filename);

    // Clean up
    if (handle != NULL) {
        cmsIT8Free(handle);
    }
    cmsDeleteContext(context);
    remove(filename);

    return 0;
}