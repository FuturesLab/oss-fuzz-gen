#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Initialize htp_tx_t object
    htp_tx_t *tx = htp_tx_create(NULL);
    if (tx == NULL) {
        return 0;
    }

    // Ensure that the data size is sufficient to create a non-empty string
    if (size < 1) {
        htp_tx_destroy(tx);
        return 0;
    }

    // Create a null-terminated string from the data
    char *param_name = (char *)malloc(size + 1);
    if (param_name == NULL) {
        htp_tx_destroy(tx);
        return 0;
    }
    memcpy(param_name, data, size);
    param_name[size] = '\0';

    // Call the function-under-test
    htp_param_t *param = htp_tx_req_get_param(tx, param_name, size);

    // Clean up
    free(param_name);
    htp_tx_destroy(tx);

    return 0;
}