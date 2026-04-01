#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for extracting an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize htp_tx_t structure
    htp_tx_t tx;
    memset(&tx, 0, sizeof(htp_tx_t));

    // Extract an int from the data
    int protocol_number = *((int *)data);

    // Call the function-under-test
    htp_tx_res_set_protocol_number(&tx, protocol_number);

    return 0;
}