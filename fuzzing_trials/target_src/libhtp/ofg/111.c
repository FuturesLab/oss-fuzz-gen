#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy
#include "/src/libhtp/htp/htp.h" // Correct path for htp.h

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Allocate memory for htp_tx_t structure
    htp_tx_t *tx = (htp_tx_t *)malloc(sizeof(htp_tx_t));
    if (tx == NULL) {
        return 0;
    }

    // Extract an integer from the input data
    int protocol_number;
    memcpy(&protocol_number, data, sizeof(int));

    // Call the function-under-test
    htp_tx_res_set_protocol_number(tx, protocol_number);

    // Clean up
    free(tx);

    return 0;
}