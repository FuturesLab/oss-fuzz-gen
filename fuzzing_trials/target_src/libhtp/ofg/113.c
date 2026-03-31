#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libhtp/htp/htp.h" // Include the appropriate header for the function-under-test

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a meaningful test
    if (size < 1) {
        return 0;
    }

    // Initialize htp_tx_t structure
    htp_tx_t tx;
    memset(&tx, 0, sizeof(htp_tx_t));

    // Allocate memory for the status message
    char *status_message = (char *)malloc(size + 1);
    if (status_message == NULL) {
        return 0;
    }

    // Copy the data into the status message and null-terminate it
    memcpy(status_message, data, size);
    status_message[size] = '\0';

    // Choose an allocation strategy
    enum htp_alloc_strategy_t alloc_strategy = HTP_ALLOC_REUSE;

    // Call the function-under-test
    htp_status_t result = htp_tx_res_set_status_message(&tx, status_message, size, alloc_strategy);

    // Free allocated memory
    free(status_message);

    return 0;
}