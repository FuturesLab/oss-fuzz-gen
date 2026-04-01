#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    // Include the necessary TIFF headers
    #include <tiff.h>
    #include <tiffio.h>
}

// Remove the redefinition of TIFFCIELabToRGB since it's already defined in the included headers

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to initialize the structures
    if (size < sizeof(TIFFDisplay) + 3 * sizeof(float)) {
        return 0;
    }

    // Initialize TIFFCIELabToRGB structure
    TIFFCIELabToRGB cielabToRGB;
    cielabToRGB.X0 = 0.95047f;
    cielabToRGB.Y0 = 1.00000f;
    cielabToRGB.Z0 = 1.08883f;

    // Initialize TIFFDisplay structure from the input data
    TIFFDisplay display;
    memcpy(&display, data, sizeof(TIFFDisplay));

    // Initialize the float array from the input data
    float refWhite[3];
    memcpy(refWhite, data + sizeof(TIFFDisplay), 3 * sizeof(float));

    // Call the function-under-test
    int result = TIFFCIELabToRGBInit(&cielabToRGB, &display, refWhite);

    return 0;
}