#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h> // Ensure this header is available for hts_md5_context

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Initialize the md5 context using the correct function
    hts_md5_context *md5_ctx = hts_md5_init();
    if (md5_ctx == NULL) {
        return 0; // Exit if initialization fails
    }

    // Call the function-under-test
    hts_md5_update(md5_ctx, data, (unsigned long)size);

    // Clean up and free the md5 context
    hts_md5_destroy(md5_ctx);

    return 0;
}