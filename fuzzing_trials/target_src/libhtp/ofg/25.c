#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libhtp/htp/htp.h" // Correct path for the header file

// Remove the extern "C" linkage specification for C code
int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Allocate and initialize htp_tx_t structure
    htp_tx_t *tx = (htp_tx_t *)malloc(sizeof(htp_tx_t));
    if (tx == NULL) {
        return 0;
    }
    memset(tx, 0, sizeof(htp_tx_t));

    // Use part of the input data as the method string
    const char *method = (const char *)data;
    size_t method_len = size;

    // Use the first byte of data to determine the allocation strategy
    enum htp_alloc_strategy_t alloc_strategy = (enum htp_alloc_strategy_t)(data[0] % 4); // Assuming there are 4 strategies

    // Call the function-under-test
    htp_status_t status = htp_tx_req_set_method(tx, method, method_len, alloc_strategy);

    // Clean up
    free(tx);

    return 0;
}