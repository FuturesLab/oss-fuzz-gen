#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Initialize htp_tx_t structure
    htp_tx_t *tx = htp_tx_create(NULL);
    if (tx == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Ensure the data is not NULL and size is greater than zero
    if (data == NULL || size == 0) {
        htp_tx_destroy(tx);
        return 0;
    }

    // Call the function-under-test
    htp_status_t status = htp_tx_res_process_body_data(tx, data, size);

    // Clean up
    htp_tx_destroy(tx);

    return 0;
}