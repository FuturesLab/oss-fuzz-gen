extern "C" {
    #include <tiffio.h>
    #include <stdint.h>
    #include <string.h> // Include string.h for memcpy
}

extern "C" int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFYCbCrToRGB) + 3 * sizeof(uint32_t)) {
        return 0; // Not enough data to proceed
    }

    // Initialize parameters for TIFFYCbCrtoRGB
    TIFFYCbCrToRGB ycbcrToRGB;
    uint32_t Y = 0;
    int32_t Cb = 0;
    int32_t Cr = 0;
    uint32_t R = 0;
    uint32_t G = 0;
    uint32_t B = 0;

    // Copy data to the TIFFYCbCrToRGB structure
    memcpy(&ycbcrToRGB, data, sizeof(TIFFYCbCrToRGB));

    // Extract Y, Cb, Cr values from the input data
    if (size >= sizeof(TIFFYCbCrToRGB) + sizeof(uint32_t)) {
        Y = *(uint32_t *)(data + sizeof(TIFFYCbCrToRGB));
    }
    if (size >= sizeof(TIFFYCbCrToRGB) + sizeof(uint32_t) + sizeof(int32_t)) {
        Cb = *(int32_t *)(data + sizeof(TIFFYCbCrToRGB) + sizeof(uint32_t));
    }
    if (size >= sizeof(TIFFYCbCrToRGB) + sizeof(uint32_t) + 2 * sizeof(int32_t)) {
        Cr = *(int32_t *)(data + sizeof(TIFFYCbCrToRGB) + sizeof(uint32_t) + sizeof(int32_t));
    }

    // Call the function-under-test
    TIFFYCbCrtoRGB(&ycbcrToRGB, Y, Cb, Cr, &R, &G, &B);

    return 0;
}