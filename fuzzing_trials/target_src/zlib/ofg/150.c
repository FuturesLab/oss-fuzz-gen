#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <sys/types.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    uLong adler = adler32(0L, Z_NULL, 0);

    if (size > 0) {
        adler = adler32(adler, data, size);
    }

    return 0;
}