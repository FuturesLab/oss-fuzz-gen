#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_codec.h>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to split into two strings
    if (size < 2) return 0;

    // Create a codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx)); // Initialize the codec context

    // Split the input data into two strings
    size_t half_size = size / 2;
    const char *option_name = reinterpret_cast<const char *>(data);
    const char *option_value = reinterpret_cast<const char *>(data + half_size);

    // Ensure both strings are null-terminated
    char *option_name_copy = static_cast<char *>(malloc(half_size + 1));
    char *option_value_copy = static_cast<char *>(malloc(size - half_size + 1));
    if (!option_name_copy || !option_value_copy) {
        free(option_name_copy);
        free(option_value_copy);
        return 0;
    }
    memcpy(option_name_copy, option_name, half_size);
    memcpy(option_value_copy, option_value, size - half_size);
    option_name_copy[half_size] = '\0';
    option_value_copy[size - half_size] = '\0';

    // Call the function under test
    aom_codec_err_t result = aom_codec_set_option(&codec_ctx, option_name_copy, option_value_copy);

    // Clean up
    free(option_name_copy);
    free(option_value_copy);

    return 0;
}