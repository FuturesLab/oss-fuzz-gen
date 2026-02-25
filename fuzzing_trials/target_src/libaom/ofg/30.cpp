#include <cstdint>
#include <cstdlib>
#include <aom/aom_codec.h>

extern "C" {

const char * aom_codec_err_to_string(aom_codec_err_t error);

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure that the input size is appropriate for our test
    if (size < sizeof(aom_codec_err_t)) {
        return 0; // Not enough data to form a valid aom_codec_err_t
    }

    // Initialize the aom_codec_err_t variable from the input data
    aom_codec_err_t error = static_cast<aom_codec_err_t>(data[0] % AOM_CODEC_ERROR); // Use modulo to keep it within bounds

    // Call the function under test
    const char *error_string = aom_codec_err_to_string(error);

    // Optionally, you can use the error_string for further processing or logging
    // Here, we just return 0 to indicate successful execution
    return 0;
}

}