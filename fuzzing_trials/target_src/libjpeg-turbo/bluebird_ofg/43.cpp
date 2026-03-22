#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h" // For close() and remove()

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    tjhandle handle = NULL;
    char filename[] = "/tmp/fuzzimageXXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Initialize TurboJPEG handle
    handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        remove(filename);
        return 0;
    }

    // Ensure size is large enough for width, height, and pixel data
    if (size < 6) {
        tj3Destroy(handle);
        remove(filename);
        return 0;
    }

    // Extract width and height from the data
    int width = (int)data[0] + 1; // Avoid zero width
    int height = (int)data[1] + 1; // Avoid zero height

    // Calculate number of pixels
    size_t numPixels = width * height;

    // Ensure data size is sufficient for pixel data
    if (size < 6 + numPixels * sizeof(uint8_t)) {
        tj3Destroy(handle);
        remove(filename);
        return 0;
    }

    // Prepare pixel data
    uint8_t *pixels = (uint8_t *)malloc(numPixels * sizeof(uint8_t));
    if (!pixels) {
        tj3Destroy(handle);
        remove(filename);
        return 0;
    }
    memcpy(pixels, data + 6, numPixels * sizeof(uint8_t));

    // Call the function-under-test
    int result = tj3SaveImage8(handle, filename, pixels, width, 0, height, TJPF_GRAY);

    // Clean up
    free(pixels);
    tj3Destroy(handle);
    remove(filename);

    return 0;
}