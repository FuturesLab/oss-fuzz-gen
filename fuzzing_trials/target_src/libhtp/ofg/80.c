#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Declare and initialize the htp_tx_t structure
    htp_tx_t tx;
    // Initialize the structure with some non-NULL values
    tx.is_config_shared = 1; // Assuming a boolean-like field for demonstration

    // Call the function-under-test
    int result = htp_tx_get_is_config_shared(&tx);

    // Use the result in some way to avoid compiler optimizations
    if (result == 0) {
        // Do something if needed
    }

    return 0;
}