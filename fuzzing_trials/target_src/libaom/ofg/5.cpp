extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int version = aom_codec_version();

    // To ensure the function is called and the result is used, we can print it
    // or use it in some meaningful way. Here, we'll just ensure it's not zero.
    if (version == 0) {
        return 0; // This is just a placeholder for any potential handling.
    }

    return 0;
}