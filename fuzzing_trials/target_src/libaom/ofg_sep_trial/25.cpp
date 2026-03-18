#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_codec.h>

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Ensure size is sufficient for non-null strings
    if (size < 2) {
        return 0;
    }

    // Split the data into two parts for the option name and value
    size_t half_size = size / 2;
    size_t option_name_len = half_size;
    size_t option_value_len = size - half_size;

    // Allocate and copy option name
    char *option_name = static_cast<char *>(malloc(option_name_len + 1));
    if (option_name == nullptr) {
        return 0;
    }
    memcpy(option_name, data, option_name_len);
    option_name[option_name_len] = '\0';

    // Allocate and copy option value
    char *option_value = static_cast<char *>(malloc(option_value_len + 1));
    if (option_value == nullptr) {
        free(option_name);
        return 0;
    }
    memcpy(option_value, data + half_size, option_value_len);
    option_value[option_value_len] = '\0';

    // Call the function under test
    aom_codec_err_t result = aom_codec_set_option(&codec_ctx, option_name, option_value);

    // Free allocated memory
    free(option_name);
    free(option_value);

    return 0;
}