#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    tjhandle handle = NULL;
    const char *filename = "dummy_image.ppm";
    int width = 0;
    int pitch = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB;

    // Create a TurboJPEG decompressor handle
    handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    // Ensure the data is not NULL and has a reasonable size
    if (data == NULL || size == 0) {
        tjDestroy(handle);
        return 0;
    }

    // Write the input data to a temporary file to simulate a real image file
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        tjDestroy(handle);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Call the function-under-test
    unsigned short *image = tj3LoadImage16(handle, filename, &width, pitch, &height, &pixelFormat);

    // Clean up
    if (image != NULL) {
        tj3Free(image);  // Correct function to free image loaded by tj3LoadImage16
    }
    tjDestroy(handle);

    return 0;
}