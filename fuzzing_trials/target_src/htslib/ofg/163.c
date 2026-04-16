#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h> // Ensure the HTSlib library is included

// Remove 'extern "C"' as it is not valid in C code
int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    // Declare a pointer for hts_md5_context
    hts_md5_context *md5_ctx;

    // Initialize the MD5 context
    md5_ctx = hts_md5_init();
    if (md5_ctx == NULL) {
        return 0; // Return if initialization fails
    }

    // Use the input data to update the MD5 context
    if (size > 0) {
        hts_md5_update(md5_ctx, data, size);
    }

    // Call the function-under-test
    hts_md5_destroy(md5_ctx);

    return 0;
}