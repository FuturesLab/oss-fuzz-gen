#include <stdint.h>
#include <stddef.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    // Ensure we have enough data to fill the htsFormat structure
    if (size < sizeof(htsFormat)) {
        return 0;
    }

    // Cast the input data to an htsFormat pointer
    const htsFormat *format = (const htsFormat *)data;

    // Call the function-under-test
    const char *extension = hts_format_file_extension(format);

    // Use the extension in some way to avoid compiler optimizations removing the call
    if (extension != NULL) {
        // Do something trivial with the extension, like checking its length
        size_t ext_length = 0;
        while (extension[ext_length] != '\0') {
            ext_length++;
        }
    }

    return 0;
}