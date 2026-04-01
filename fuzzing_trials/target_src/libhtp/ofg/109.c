#include <stdint.h>
#include <stdlib.h>
#include <htp/htp.h>

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Initialize the configuration
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        return 0; // If configuration creation fails, exit
    }

    // Call the function-under-test
    htp_connp_t *connp = htp_connp_create(cfg);
    if (connp != NULL && data != NULL && size > 0) {
        // Feed the input data to the connection parser
        htp_connp_req_data(connp, NULL, data, size);
    }

    // Clean up
    if (connp != NULL) {
        htp_connp_destroy(connp);
    }
    htp_config_destroy(cfg);

    return 0;
}