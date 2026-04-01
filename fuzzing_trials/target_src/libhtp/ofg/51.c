#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/libhtp/htp/htp.h" // Correct path for the htp.h header file

// Dummy callback function with the correct signature
int response_body_data_callback(htp_tx_data_t *data) {
    // Implement a simple callback logic, if needed
    return 0; // Return an integer as expected by the callback signature
}

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Create a configuration object
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Create a dummy connection parser object with the configuration
    htp_connp_t *connp = htp_connp_create(cfg);
    if (connp == NULL) {
        htp_config_destroy(cfg); // Clean up configuration
        return 0; // Exit if memory allocation fails
    }

    // Allocate and initialize htp_tx_t object using the connection parser
    htp_tx_t *tx = htp_tx_create(connp);
    if (tx == NULL) {
        htp_connp_destroy_all(connp); // Clean up connection parser
        htp_config_destroy(cfg); // Clean up configuration
        return 0; // Exit if memory allocation fails
    }

    // Register the response body data callback
    htp_tx_register_response_body_data(tx, response_body_data_callback);

    // Simulate feeding data into the transaction
    htp_tx_req_process_body_data(tx, data, size);

    // Clean up
    htp_tx_destroy(tx); // Use the library's function to properly destroy the transaction
    htp_connp_destroy_all(connp); // Clean up connection parser
    htp_config_destroy(cfg); // Clean up configuration

    return 0;
}