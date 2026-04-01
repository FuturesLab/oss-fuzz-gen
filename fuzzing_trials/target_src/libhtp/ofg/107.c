#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Initialize the HTP configuration
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        return 0; // If configuration creation fails, exit early
    }

    // Initialize the HTP connection parser
    htp_connp_t *connp = htp_connp_create(cfg);
    if (connp == NULL) {
        htp_config_destroy(cfg);
        return 0; // If connection parser creation fails, exit early
    }

    // Feed the input data to the connection parser
    htp_status_t status = htp_connp_req_data(connp, NULL, data, size);

    // Check the status and call the function-under-test if appropriate
    if (status == HTP_OK) {
        // Process any remaining data
        htp_connp_req_data(connp, NULL, NULL, 0);
    }

    // Clean up
    htp_connp_destroy_all(connp);
    htp_config_destroy(cfg);

    return 0;
}