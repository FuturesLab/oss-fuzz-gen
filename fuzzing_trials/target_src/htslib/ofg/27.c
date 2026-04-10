#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"  // Assuming htslib is installed and available
#include "/src/htslib/htslib/hts.h"  // Include the correct header for MD5 functions

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    if (size < 16) {
        // Not enough data to proceed
        return 0;
    }

    // Allocate memory for the output
    unsigned char output[16];  // MD5 outputs are typically 16 bytes

    // Initialize the MD5 context
    hts_md5_context *ctx = hts_md5_init();
    if (ctx == NULL) {
        return 0;
    }

    // Update the MD5 context with the input data
    hts_md5_update(ctx, data, size);

    // Call the function-under-test
    hts_md5_final(output, ctx);

    // Clean up
    hts_md5_destroy(ctx);

    return 0;
}