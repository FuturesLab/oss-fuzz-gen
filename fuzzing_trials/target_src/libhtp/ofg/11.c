#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htp/htp.h>

// Correct type name for the enumeration
typedef int htp_alloc_strategy_t;  // This is a placeholder; replace with the actual type if different

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a non-empty string and enum
    if (size < 2) {
        return 0;
    }

    // Initialize htp_tx_t structure
    htp_tx_t *tx = htp_tx_create(NULL);
    if (tx == NULL) {
        return 0;
    }

    // Allocate memory for the status line string
    char *status_line = (char *)malloc(size + 1);
    if (status_line == NULL) {
        htp_tx_destroy(tx);
        return 0;
    }

    // Copy data to status line and null-terminate it
    memcpy(status_line, data, size);
    status_line[size] = '\0';

    // Use the first byte of data as the enum value
    htp_alloc_strategy_t alloc_strategy = (htp_alloc_strategy_t)data[0];

    // Call the function-under-test
    htp_status_t status = htp_tx_res_set_status_line(tx, status_line, size, alloc_strategy);

    // Clean up
    free(status_line);
    htp_tx_destroy(tx);

    return 0;
}