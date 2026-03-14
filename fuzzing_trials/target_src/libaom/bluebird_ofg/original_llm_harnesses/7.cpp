extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Since aom_codec_version() does not take any parameters, we can call it directly
    int version = aom_codec_version();

    // Optionally, you can use the version value for further processing or logging
    // For fuzzing purposes, we just call the function to ensure it is executed
    (void)version; // Suppress unused variable warning

    return 0;
}