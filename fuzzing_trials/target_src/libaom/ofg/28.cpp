extern "C" {
    #include <aom/aom_codec.h>
    #include <stdio.h>  // Include the standard I/O library for printf
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version_extra = aom_codec_version_extra_str();

    // Ensure the result is not NULL and perform some basic operations
    if (version_extra != NULL) {
        // Print the version extra string for debugging purposes
        // Note: In actual fuzzing, printing might be disabled for performance reasons
        printf("Version Extra: %s\n", version_extra);
    }

    return 0;
}