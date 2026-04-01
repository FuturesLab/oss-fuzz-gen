#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htp/htp.h>

// Include the necessary header for the enum
#include <htp/htp_config_auto.h>

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a non-empty URI and allocation strategy
    if (size < 2) {
        return 0;
    }

    // Initialize the transaction object
    htp_tx_t *tx = htp_tx_create(NULL);

    // Allocate memory for the URI string, ensuring it's null-terminated
    char *uri = (char *)malloc(size + 1);
    if (uri == NULL) {
        htp_tx_destroy(tx);
        return 0;
    }
    memcpy(uri, data, size);
    uri[size] = '\0';

    // Extract the allocation strategy from the data
    enum htp_alloc_strategy_t alloc_strategy = (enum htp_alloc_strategy_t)(data[0] % 3); // Assuming there are 3 strategies

    // Call the function-under-test
    htp_status_t status = htp_tx_req_set_uri(tx, uri, size, alloc_strategy);

    // Clean up
    free(uri);
    htp_tx_destroy(tx);

    return 0;
}