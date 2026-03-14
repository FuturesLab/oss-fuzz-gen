#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Assuming the aom_codec_version function is defined in the linked library
extern "C" {
    int aom_codec_version();
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int version = aom_codec_version();

    // Print the version for debugging purposes
    printf("AOM Codec Version: %d\n", version);

    return 0;
}