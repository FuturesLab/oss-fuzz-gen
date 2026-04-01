// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjSaveImage at turbojpeg.c:3128:15 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tj3LoadImage16 at turbojpeg-mp.c:434:21 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3Free at turbojpeg.c:890:16 in turbojpeg.h
// tjLoadImage at turbojpeg.c:3107:26 in turbojpeg.h
// tjGetErrorStr2 at turbojpeg.c:630:17 in turbojpeg.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <turbojpeg.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void fuzz_tjSaveImage(const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure minimum size for meaningful data

    const char *filename = "./dummy_file";
    int width = Data[0] + 1; // Avoid zero width
    int pitch = Data[1] + 1; // Avoid zero pitch
    int height = Data[2] + 1; // Avoid zero height
    int pixelFormat = Data[3] % TJ_NUMPF;
    int flags = Data[4];

    // Correct buffer size calculation
    size_t bufferSize = static_cast<size_t>(pitch) * height * tjPixelSize[pixelFormat];
    if (bufferSize > Size - 5) return; // Ensure buffer size does not exceed input size

    unsigned char *buffer = new unsigned char[bufferSize];
    memcpy(buffer, Data + 5, bufferSize);

    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    int result = tjSaveImage(filename, buffer, width, pitch, height, pixelFormat, flags);

    if (result == -1) {
        const char *errStr = tjGetErrorStr();
        if (errStr) {
            printf("tjSaveImage Error: %s\n", errStr);
        }
    }

    delete[] buffer;
}

static void fuzz_tj3LoadImage16(const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure minimum size for meaningful data

    const char *filename = "./dummy_file";
    int width = 0, height = 0, pixelFormat = TJPF_RGB;
    int align = 1 << (Data[0] % 3); // Align to 1, 2, or 4
    tjhandle handle = nullptr;

    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    unsigned short *image = tj3LoadImage16(handle, filename, &width, align, &height, &pixelFormat);
    if (!image) {
        const char *errStr = tj3GetErrorStr(handle);
        if (errStr) {
            printf("tj3LoadImage16 Error: %s\n", errStr);
        }
    } else {
        tj3Free(image);
    }
}

static void fuzz_tjLoadImage(const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure minimum size for meaningful data

    const char *filename = "./dummy_file";
    int width = 0, height = 0, pixelFormat = TJPF_RGB;
    int align = 1 << (Data[0] % 3); // Align to 1, 2, or 4
    int flags = Data[1];

    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    unsigned char *image = tjLoadImage(filename, &width, align, &height, &pixelFormat, flags);
    if (!image) {
        const char *errStr = tjGetErrorStr2(nullptr);
        if (errStr) {
            printf("tjLoadImage Error: %s\n", errStr);
        }
    } else {
        free(image);
    }
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    fuzz_tjSaveImage(Data, Size);
    fuzz_tj3LoadImage16(Data, Size);
    fuzz_tjLoadImage(Data, Size);
    return 0;
}