#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <tiffio.h>
    #include <tiff.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for tif_dir.h
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of TIFFField
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Cast the input data to a TIFFField pointer
    const TIFFField *field = reinterpret_cast<const TIFFField *>(data);

    // Call the function-under-test
    int result = TIFFFieldIsAnonymous(field);

    // Use the result to prevent the compiler from optimizing away the call
    if (result) {
        // Do something if the field is anonymous
    } else {
        // Do something if the field is not anonymous
    }

    return 0;
}