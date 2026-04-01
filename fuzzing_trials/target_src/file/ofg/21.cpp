#include <stdint.h>
#include <stddef.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure the size is adequate for extracting an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data
    int flags = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    magic_t magic_cookie = magic_open(flags);

    // Clean up if magic_open was successful
    if (magic_cookie != NULL) {
        magic_close(magic_cookie);
    }

    return 0;
}