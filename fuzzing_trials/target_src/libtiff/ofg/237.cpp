#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    void TIFFXYZToRGB(TIFFCIELabToRGB *, float, float, float, uint32_t *, uint32_t *, uint32_t *);
}

extern "C" int LLVMFuzzerTestOneInput_237(const uint8_t *data, size_t size) {
    if (size < sizeof(float) * 3 + sizeof(TIFFCIELabToRGB)) {
        return 0;
    }

    // Initialize the TIFFCIELabToRGB structure
    TIFFCIELabToRGB cielab;
    cielab.range = 255; // Example initialization, adjust as needed
    cielab.Y0 = 100.0f; // Example initialization, adjust as needed
    cielab.X0 = 95.047f; // Example initialization, adjust as needed
    cielab.Z0 = 108.883f; // Example initialization, adjust as needed

    // Extract float values from the data
    float X = *reinterpret_cast<const float*>(data);
    float Y = *reinterpret_cast<const float*>(data + sizeof(float));
    float Z = *reinterpret_cast<const float*>(data + 2 * sizeof(float));

    // Initialize the output RGB values
    uint32_t R, G, B;

    // Call the function-under-test
    TIFFXYZToRGB(&cielab, X, Y, Z, &R, &G, &B);

    return 0;
}