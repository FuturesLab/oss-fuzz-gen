// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3YUVPlaneWidth at turbojpeg.c:1057:15 in turbojpeg.h
// tjPlaneSizeYUV at turbojpeg.c:1048:25 in turbojpeg.h
// tjPlaneWidth at turbojpeg.c:1083:15 in turbojpeg.h
// tjPlaneHeight at turbojpeg.c:1117:15 in turbojpeg.h
// tj3YUVPlaneSize at turbojpeg.c:1020:18 in turbojpeg.h
// tj3YUVPlaneHeight at turbojpeg.c:1091:15 in turbojpeg.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <turbojpeg.h>

static void fuzz_tj3YUVPlaneWidth(const uint8_t* Data, size_t Size) {
    if (Size < 3) return;
    int componentID = Data[0] % 3;  // Valid component IDs: 0, 1, 2
    int width = Data[1];
    int subsamp = Data[2] % 6;  // Assuming 6 subsampling options

    tj3YUVPlaneWidth(componentID, width, subsamp);
}

static void fuzz_tjPlaneSizeYUV(const uint8_t* Data, size_t Size) {
    if (Size < 5) return;
    int componentID = Data[0] % 3;
    int width = Data[1];
    int stride = Data[2];
    int height = Data[3];
    int subsamp = Data[4] % 6;

    tjPlaneSizeYUV(componentID, width, stride, height, subsamp);
}

static void fuzz_tjPlaneWidth(const uint8_t* Data, size_t Size) {
    if (Size < 3) return;
    int componentID = Data[0] % 3;
    int width = Data[1];
    int subsamp = Data[2] % 6;

    tjPlaneWidth(componentID, width, subsamp);
}

static void fuzz_tjPlaneHeight(const uint8_t* Data, size_t Size) {
    if (Size < 3) return;
    int componentID = Data[0] % 3;
    int height = Data[1];
    int subsamp = Data[2] % 6;

    tjPlaneHeight(componentID, height, subsamp);
}

static void fuzz_tj3YUVPlaneSize(const uint8_t* Data, size_t Size) {
    if (Size < 5) return;
    int componentID = Data[0] % 3;
    int width = Data[1];
    int stride = Data[2];
    int height = Data[3];
    int subsamp = Data[4] % 6;

    tj3YUVPlaneSize(componentID, width, stride, height, subsamp);
}

static void fuzz_tj3YUVPlaneHeight(const uint8_t* Data, size_t Size) {
    if (Size < 3) return;
    int componentID = Data[0] % 3;
    int height = Data[1];
    int subsamp = Data[2] % 6;

    tj3YUVPlaneHeight(componentID, height, subsamp);
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    fuzz_tj3YUVPlaneWidth(Data, Size);
    fuzz_tjPlaneSizeYUV(Data, Size);
    fuzz_tjPlaneWidth(Data, Size);
    fuzz_tjPlaneHeight(Data, Size);
    fuzz_tj3YUVPlaneSize(Data, Size);
    fuzz_tj3YUVPlaneHeight(Data, Size);

    return 0;
}