#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/kstring.h>
#include <htslib/hts_defs.h> // Include for hts_md5_context

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Initialize the context
    hts_md5_context *ctx = hts_md5_init();

    if (ctx == NULL) {
        return 0; // Exit if initialization fails
    }

    // Use the input data to update the MD5 context
    hts_md5_update(ctx, data, size);

    // Finalize the MD5 computation
    unsigned char md5_result[16];
    hts_md5_final(md5_result, ctx);

    // Destroy the context
    hts_md5_destroy(ctx);

    return 0;
}