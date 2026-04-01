#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

extern "C" {
    int TIFFCIELabToRGBInit(TIFFCIELabToRGB *, const TIFFDisplay *, float *);
}

extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFDisplay) + 3 * sizeof(float)) {
        return 0;
    }

    // Allocate and initialize TIFFCIELabToRGB structure
    TIFFCIELabToRGB cielabToRGB;
    memset(&cielabToRGB, 0, sizeof(TIFFCIELabToRGB));

    // Initialize TIFFDisplay structure from the input data
    TIFFDisplay display;
    memcpy(&display, data, sizeof(TIFFDisplay));

    // Initialize float array from the input data
    float xyz[3];
    memcpy(xyz, data + sizeof(TIFFDisplay), 3 * sizeof(float));

    // Call the function-under-test
    TIFFCIELabToRGBInit(&cielabToRGB, &display, xyz);

    return 0;
}