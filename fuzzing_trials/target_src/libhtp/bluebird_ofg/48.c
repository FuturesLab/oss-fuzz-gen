#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memset
#include "htp/htp.h"  // Correct path for the header file
#include "/src/libhtp/htp/htp_config.h" // Include for htp_cfg_t definition

// Remove the 'extern "C"' as it is not valid in C code
int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for our needs
    if (size < sizeof(int)) {
        return 0;
    }

    // Allocate and initialize htp_tx_t
    htp_tx_t *tx = (htp_tx_t *)malloc(sizeof(htp_tx_t));
    if (tx == NULL) {
        return 0;
    }

    // Initialize the htp_tx_t structure
    // Assuming there are init functions or zeroing is sufficient
    // If there are specific init functions, replace the following with those
    memset(tx, 0, sizeof(htp_tx_t));

    // Create and configure htp_cfg_t using the provided function
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        free(tx);
        return 0;
    }

    // Extract an integer from the data for the third parameter
    int config_value = *(int *)data;

    // Call the function-under-test
    htp_tx_set_config(tx, cfg, config_value);

    // Clean up
    free(tx);
    htp_config_destroy(cfg);

    return 0;
}