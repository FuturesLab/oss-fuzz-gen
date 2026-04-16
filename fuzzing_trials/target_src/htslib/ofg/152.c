#include <stdint.h>
#include <stdlib.h>
#include "/src/htslib/htslib/hts.h" // Correct path for necessary header

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Call the function-under-test
    hts_md5_context *ctx = hts_md5_init();

    // Check if the context was initialized successfully
    if (ctx != NULL) {
        // Perform operations with ctx if needed
        // For example, feed the data to the MD5 context
        hts_md5_update(ctx, data, size);

        // Clean up the context
        hts_md5_destroy(ctx);
    }

    return 0;
}