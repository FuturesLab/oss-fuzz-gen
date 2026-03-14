#include <cstdint>
#include <cstddef>
#include <cstring>
#include <aom/aom_codec.h>

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Ensure there is enough data for at least two strings and context
    if (size < 3) return 0;

    // Initialize aom_codec_ctx_t
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Find positions to split the input data into two strings
    size_t pos1 = size / 3;
    size_t pos2 = 2 * size / 3;

    // Allocate memory for the strings and ensure null termination
    char *option_name = new char[pos1 + 1];
    char *option_value = new char[size - pos2 + 1];

    memcpy(option_name, data, pos1);
    option_name[pos1] = '\0';

    memcpy(option_value, data + pos2, size - pos2);
    option_value[size - pos2] = '\0';

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_set_option(&codec_ctx, option_name, option_value);

    // Clean up
    delete[] option_name;
    delete[] option_value;

    return 0;
}