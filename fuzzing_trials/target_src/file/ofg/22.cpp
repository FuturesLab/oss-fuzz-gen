#include <cstdint>
#include <cstdlib>
#include <climits>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to extract an integer value.
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer value from the input data.
    int flags = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        flags |= static_cast<int>(data[i]) << (i * CHAR_BIT);
    }

    // Call the function-under-test.
    magic_t magic_cookie = magic_open(flags);

    // Clean up if necessary.
    if (magic_cookie != nullptr) {
        magic_close(magic_cookie);
    }

    return 0;
}