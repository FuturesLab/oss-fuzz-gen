#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include this for memcpy

extern "C" {
    #include <tiffio.h>
    #include <tiff.h>
}

extern "C" int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFCIELabToRGB) + sizeof(uint32_t) + 2 * sizeof(int32_t) + 3 * sizeof(float)) {
        return 0;
    }

    TIFFCIELabToRGB cielab;
    uint32_t sampleIndex = 0;
    int32_t L = 0;
    int32_t a = 0;
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

    // Initialize the TIFFCIELabToRGB structure
    cielab.range = 100.0f;
    cielab.Y0 = 1.0f;
    cielab.X0 = 1.0f;
    cielab.Z0 = 1.0f;

    // Extract values from the data buffer
    if (size >= sizeof(TIFFCIELabToRGB)) {
        memcpy(&cielab, data, sizeof(TIFFCIELabToRGB));
        data += sizeof(TIFFCIELabToRGB);
        size -= sizeof(TIFFCIELabToRGB);
    }
    if (size >= sizeof(uint32_t)) {
        memcpy(&sampleIndex, data, sizeof(uint32_t));
        data += sizeof(uint32_t);
        size -= sizeof(uint32_t);
    }
    if (size >= sizeof(int32_t)) {
        memcpy(&L, data, sizeof(int32_t));
        data += sizeof(int32_t);
        size -= sizeof(int32_t);
    }
    if (size >= sizeof(int32_t)) {
        memcpy(&a, data, sizeof(int32_t));
        data += sizeof(int32_t);
        size -= sizeof(int32_t);
    }
    if (size >= sizeof(float)) {
        memcpy(&X, data, sizeof(float));
        data += sizeof(float);
        size -= sizeof(float);
    }
    if (size >= sizeof(float)) {
        memcpy(&Y, data, sizeof(float));
        data += sizeof(float);
        size -= sizeof(float);
    }
    if (size >= sizeof(float)) {
        memcpy(&Z, data, sizeof(float));
        data += sizeof(float);
        size -= sizeof(float);
    }

    // Call the function-under-test
    TIFFCIELabToXYZ(&cielab, sampleIndex, L, a, &X, &Y, &Z);

    return 0;
}