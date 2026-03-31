#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Check if the size of data is sufficient to create a valid htp_tx_t object
    if (size < sizeof(htp_tx_t)) {
        return 0;
    }

    // Allocate memory for htp_tx_t object
    htp_tx_t *tx = (htp_tx_t *)malloc(sizeof(htp_tx_t));
    if (tx == NULL) {
        return 0;
    }

    // Initialize the htp_tx_t object with data
    // Ensure that the data is not NULL and size is sufficient
    memcpy(tx, data, sizeof(htp_tx_t));

    // Call the function-under-test
    int result = htp_tx_req_has_body(tx);

    // Free allocated memory
    free(tx);

    return 0;
}