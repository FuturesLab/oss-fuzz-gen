#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {

const char * aom_codec_err_to_string(aom_codec_err_t error);

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Ensure that the size is within the bounds of aom_codec_err_t
    if (size < sizeof(aom_codec_err_t)) {
        return 0;
    }

    // Initialize the aom_codec_err_t variable
    aom_codec_err_t error_code = static_cast<aom_codec_err_t>(data[0]); // Using the first byte for simplicity

    // Call the function under test
    const char *error_string = aom_codec_err_to_string(error_code);

    // Optionally, you can do something with error_string, like logging or further processing
    // For this fuzzing harness, we simply return
    (void)error_string; // Prevent unused variable warning

    return 0;
}

}