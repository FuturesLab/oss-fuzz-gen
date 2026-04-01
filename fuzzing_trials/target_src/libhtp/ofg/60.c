#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memset
#include "/src/libhtp/htp/htp.h" // Correct path for htp.h

// Remove 'extern "C"' as it is not compatible with C code
int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    htp_tx_t tx;
    int protocol_version;

    // Ensure size is sufficient to extract an integer for protocol_version
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize htp_tx_t object
    // Assuming that htp_tx_t has a function to initialize it, replace with actual initialization if available
    // For this example, we assume it's zero-initialized
    memset(&tx, 0, sizeof(htp_tx_t));

    // Extract an integer from data for protocol_version
    protocol_version = *(const int *)data;

    // Call the function-under-test
    htp_tx_req_set_protocol_0_9(&tx, protocol_version);

    return 0;
}