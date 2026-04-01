#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Check if the input data is empty
    if (size == 0) {
        return 0;
    }

    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        return 0; // Exit if configuration creation failed
    }

    htp_connp_t *connp;

    // Initialize the connection parser object with a valid configuration
    connp = htp_connp_create(cfg);

    // Check if the creation was successful
    if (connp == NULL) {
        htp_config_destroy(cfg);
        return 0; // Exit if creation failed
    }

    // Create a transaction parser object
    htp_tx_t *tx = htp_connp_tx_create(connp);
    if (tx == NULL) {
        htp_connp_destroy(connp);
        htp_config_destroy(cfg);
        return 0; // Exit if transaction creation failed
    }

    // Feed the input data to the parser
    htp_status_t status = htp_connp_req_data(connp, NULL, data, size);

    // Check if feeding data was successful
    if (status != HTP_OK) {
        htp_connp_destroy(connp);
        htp_config_destroy(cfg);
        return 0; // Exit if feeding data failed
    }

    // Call the function-under-test
    htp_connp_destroy(connp);
    htp_config_destroy(cfg);

    return 0;
}