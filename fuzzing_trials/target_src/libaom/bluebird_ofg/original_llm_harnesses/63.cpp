#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the header for strlen

extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for aom_codec_ctx_t
    if (size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    // Cast the input data to aom_codec_ctx_t
    const aom_codec_ctx_t *codec_ctx = reinterpret_cast<const aom_codec_ctx_t *>(data);

    // Call the function-under-test
    const char *error_message = aom_codec_error(codec_ctx);

    // Use the result in some way to avoid compiler optimizations
    if (error_message != nullptr) {
        // Print the error message length
        volatile size_t length = strlen(error_message);
    }

    return 0;
}