// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// htp_connp_req_data at htp_request.c:985:5 in htp_connection_parser.h
// htp_connp_create at htp_connection_parser.c:77:14 in htp_connection_parser.h
// htp_connp_open at htp_connection_parser.c:174:6 in htp_connection_parser.h
// htp_connp_close at htp_connection_parser.c:59:6 in htp_connection_parser.h
// htp_connp_destroy_all at htp_connection_parser.c:131:6 in htp_connection_parser.h
// htp_connp_res_data at htp_response.c:1269:5 in htp_connection_parser.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htp.h"

// Mock function to create a default configuration
static htp_cfg_t *create_default_cfg() {
    // Use the library's configuration creation function if available
    return htp_config_create();
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    htp_cfg_t *cfg = create_default_cfg();
    if (!cfg) return 0;

    htp_connp_t *connp = htp_connp_create(cfg);
    if (!connp) {
        htp_config_destroy(cfg);
        return 0;
    }

    const char *client_addr = "127.0.0.1";
    int client_port = 12345;
    const char *server_addr = "127.0.0.1";
    int server_port = 80;
    htp_time_t timestamp = {0, 0};

    // Open the connection twice as per the order
    htp_connp_open(connp, client_addr, client_port, server_addr, server_port, &timestamp);
    htp_connp_open(connp, client_addr, client_port, server_addr, server_port, &timestamp);

    // Process request data
    htp_connp_req_data(connp, &timestamp, Data, Size);

    // Process response data
    htp_connp_res_data(connp, &timestamp, Data, Size);

    // Close the connection
    htp_connp_close(connp, &timestamp);

    // Destroy the connection once
    htp_connp_destroy_all(connp);

    // Clean up configuration
    htp_config_destroy(cfg);

    return 0;
}