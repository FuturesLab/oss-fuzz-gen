#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libhtp/htp/htp.h"

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the protocol string
    if (size < 1) {
        return 0;
    }

    // Allocate and initialize htp_tx_t
    htp_tx_t *tx = (htp_tx_t *)malloc(sizeof(htp_tx_t));
    if (tx == NULL) {
        return 0;
    }
    memset(tx, 0, sizeof(htp_tx_t));

    // Use the first byte of data to determine the allocation strategy
    enum htp_alloc_strategy_t alloc_strategy = (enum htp_alloc_strategy_t)(data[0] % 2);

    // Use the remaining data as the protocol string
    const char *protocol = (const char *)(data + 1);
    size_t protocol_len = size - 1;

    // Call the function-under-test
    htp_status_t status = htp_tx_req_set_protocol(tx, protocol, protocol_len, alloc_strategy);

    // Free allocated resources
    free(tx);

    return 0;
}