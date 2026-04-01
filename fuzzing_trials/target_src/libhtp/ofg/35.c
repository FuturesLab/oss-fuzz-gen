#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>
#include <htp/htp_connection_parser.h>

// Function prototype for the fuzzing entry point
int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Create and initialize htp_cfg_t structure
    htp_cfg_t *cfg = htp_config_create();

    // Create and initialize htp_connp_t structure
    htp_connp_t *connp = htp_connp_create(cfg);

    // Create and initialize htp_tx_t structure with the connection parser
    htp_tx_t *tx = htp_tx_create(connp);

    // Extract an integer from the input data
    int config_option = *((int *)data);

    // Call the function-under-test
    htp_tx_set_config(tx, cfg, config_option);

    // Clean up
    htp_tx_destroy(tx);
    htp_config_destroy(cfg);
    htp_connp_destroy_all(connp);

    return 0;
}