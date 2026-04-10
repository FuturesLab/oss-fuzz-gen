#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"  // Include the header where hts_md5_context is defined

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for fuzzing
    if (size < 16) {
        return 0;
    }

    // Allocate memory for the MD5 output
    unsigned char md5_output[16];

    // Allocate and initialize the MD5 context
    hts_md5_context *md5_ctx = hts_md5_init();
    if (md5_ctx == NULL) {
        return 0;
    }

    // Update the MD5 context with the input data
    hts_md5_update(md5_ctx, data, size);

    // Call the function-under-test
    hts_md5_final(md5_output, md5_ctx);

    // Free the MD5 context
    hts_md5_destroy(md5_ctx);

    return 0;
}