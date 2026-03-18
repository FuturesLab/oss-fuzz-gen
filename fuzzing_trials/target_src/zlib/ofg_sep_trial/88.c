#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Initialize the adler parameter with a non-zero value
    uLong adler = 1; 

    // Call the function-under-test
    uLong result = adler32(adler, (const Bytef *)data, (uInt)size);

    // Use the result in some way to prevent optimization out
    volatile uLong prevent_optimization = result;
    (void)prevent_optimization;

    return 0;
}