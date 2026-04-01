#include <cstdint>
#include <cstddef>
#include <cstring> // Include this for strlen

extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for an aom_codec_err_t type
    if (size < sizeof(aom_codec_err_t)) {
        return 0;
    }

    // Cast the input data to aom_codec_err_t
    aom_codec_err_t codec_err = *(reinterpret_cast<const aom_codec_err_t *>(data));

    // Call the function-under-test
    const char *error_string = aom_codec_err_to_string(codec_err);

    // Use the result in some way (e.g., print, log, etc.)
    // Here, we just ensure it is not null by checking its length
    if (error_string != nullptr) {
        volatile size_t length = strlen(error_string); // Use volatile to prevent optimization
    }

    return 0;
}