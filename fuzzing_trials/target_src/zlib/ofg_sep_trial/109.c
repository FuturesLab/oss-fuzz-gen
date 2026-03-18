#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

// Remove the 'extern "C"' as this is C code, not C++
int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    voidpc buffer = (voidpc)data;
    z_size_t size1 = size > 0 ? size : 1; // Ensure size1 is not zero
    z_size_t size2 = 1; // Setting size2 to 1 for simplicity

    // Create a temporary gzFile for writing
    gzFile gzfile = gzopen("/dev/null", "wb");
    if (gzfile == NULL) {
        return 0; // If gzopen fails, exit early
    }

    // Call the function-under-test
    gzfwrite(buffer, size1, size2, gzfile);

    // Close the gzFile
    gzclose(gzfile);

    return 0;
}