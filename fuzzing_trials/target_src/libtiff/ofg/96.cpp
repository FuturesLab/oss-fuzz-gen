extern "C" {
    #include <tiffio.h>
    #include <tiff.h> // Include this to access the definition of TIFFField
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for tif_dir.h
}

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a TIFFField object
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Create a TIFFField object from the input data
    const TIFFField *field = reinterpret_cast<const TIFFField*>(data);

    // Call the function-under-test
    TIFFDataType dataType = TIFFFieldDataType(field);

    // Use the result in some way to prevent optimizations
    (void)dataType;

    return 0;
}