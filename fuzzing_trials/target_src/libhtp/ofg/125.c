#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htp/htp.h> // Assuming the library provides this header for htp_connp_t and htp_time_t
#include <sys/time.h> // Include this for struct timeval

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Initialize the htp_cfg_t structure
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        return 0; // Exit if creation failed
    }

    // Initialize the htp_connp_t structure with a valid configuration
    htp_connp_t *connp = htp_connp_create(cfg);
    if (connp == NULL) {
        htp_config_destroy(cfg);
        return 0; // Exit if creation failed
    }

    // Initialize the struct timeval structure
    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = 0;

    // Ensure data is not NULL and size is valid
    if (data == NULL || size == 0) {
        htp_connp_destroy(connp);
        htp_config_destroy(cfg);
        return 0;
    }

    // Call the function-under-test
    htp_connp_req_data(connp, &time, data, size);

    // Clean up
    htp_connp_destroy(connp);
    htp_config_destroy(cfg);

    return 0;
}