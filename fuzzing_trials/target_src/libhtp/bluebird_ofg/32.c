#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy
#include "htp/htp.h" // Correct path for htp.h

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract an integer for status code
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize the htp_tx_t structure
    htp_tx_t *tx = (htp_tx_t *)malloc(sizeof(htp_tx_t));
    if (tx == NULL) {
        return 0;
    }

    // Extract an integer from the data for the status code
    int status_code;
    memcpy(&status_code, data, sizeof(int));

    // Call the function-under-test
    htp_tx_res_set_status_code(tx, status_code);

    // Clean up
    free(tx);

    return 0;
}