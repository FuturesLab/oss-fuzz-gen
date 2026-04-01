#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Initialize the transaction object
    htp_tx_t *tx = htp_tx_create(NULL);
    if (tx == NULL) {
        return 0;
    }

    // Ensure data is not NULL and has a valid size
    if (data == NULL || size == 0) {
        htp_tx_destroy(tx);
        return 0;
    }

    // Call the function-under-test with the transaction, data, and size
    htp_status_t status = htp_tx_req_process_body_data(tx, (const void *)data, size);

    // Cleanup
    htp_tx_destroy(tx);

    return 0;
}