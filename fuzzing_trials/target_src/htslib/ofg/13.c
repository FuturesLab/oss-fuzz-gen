#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h> // Include the header file for hts_md5_context

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize an hts_md5_context
    hts_md5_context *md5_ctx = hts_md5_init();
    if (md5_ctx == NULL) {
        return 0; // If initialization fails, return immediately
    }

    // Use the provided data as input for the hts_md5_update function
    hts_md5_update(md5_ctx, (const void *)data, (unsigned long)size);

    // Clean up the MD5 context after use
    hts_md5_destroy(md5_ctx);

    return 0;
}