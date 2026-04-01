#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>
#include <htp/htp_connection_parser.h> // Include necessary header for connection parser
#include <htp/htp_transaction.h> // Include necessary header for transaction

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize the HTP configuration
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        return 0;
    }

    // Initialize the HTP transaction
    htp_connp_t *dummy_connp = htp_connp_create(cfg); // Create a dummy connection parser for transaction
    if (dummy_connp == NULL) {
        htp_config_destroy(cfg);
        return 0;
    }
    htp_tx_t *tx = htp_tx_create(dummy_connp); // Correctly create the transaction with a connection parser
    if (tx == NULL) {
        htp_connp_destroy_all(dummy_connp);
        htp_config_destroy(cfg);
        return 0;
    }

    // Create a connection parser
    htp_connp_t *connp = htp_connp_create(cfg);
    if (connp == NULL) {
        htp_tx_destroy(tx);
        htp_connp_destroy_all(dummy_connp);
        htp_config_destroy(cfg);
        return 0;
    }

    // Feed the input data to the parser
    htp_time_t timestamp = {0}; // Create a dummy timestamp
    htp_status_t status = htp_connp_req_data(connp, &timestamp, data, size); // Pass the correct number of arguments
    
    // Check the status and proceed if successful
    if (status == HTP_OK) {
        // Clear the headers as the function under test
        htp_tx_res_set_headers_clear(tx);
    }

    // Clean up
    htp_connp_destroy_all(connp);
    htp_tx_destroy(tx);
    htp_connp_destroy_all(dummy_connp);
    htp_config_destroy(cfg);

    return 0;
}