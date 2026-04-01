#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for memcpy function
#include "/src/libhtp/htp/htp.h"  // Correct path for htp.h

// Remove 'extern "C"' as it is not compatible with C code
int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize the htp_tx_t structure
    htp_tx_t transaction;
    memset(&transaction, 0, sizeof(htp_tx_t));  // Initialize the structure to zero

    // Extract an integer from the input data
    int status_code;
    memcpy(&status_code, data, sizeof(int));

    // Call the function-under-test
    htp_tx_res_set_status_code(&transaction, status_code);

    return 0;
}