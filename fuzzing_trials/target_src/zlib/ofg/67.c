#include <stdint.h>
#include <zlib.h>  // Ensure to include the zlib header for uLong type
#include <stddef.h>
#include <sys/types.h>  // Include for off_t type

// Declare the function crc32_combine_gen if it's not declared elsewhere
extern uLong crc32_combine_gen(off_t offset);

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of an off_t type
    if (size < sizeof(off_t)) {
        return 0;
    }

    // Extract an off_t value from the input data
    off_t offset = 0;
    for (size_t i = 0; i < sizeof(off_t); i++) {
        offset = (offset << 8) | data[i];
    }

    // Call the function-under-test
    uLong result = crc32_combine_gen(offset);

    // Use the result in some way to avoid any compiler optimizations
    (void)result;

    return 0;
}