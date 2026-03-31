// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// htp_connp_get_user_data at htp_connection_parser.c:162:7 in htp_connection_parser.h
// htp_connp_get_out_tx at htp_connection_parser.c:157:11 in htp_connection_parser.h
// htp_connp_get_in_tx at htp_connection_parser.c:147:11 in htp_connection_parser.h
// htp_connp_tx_create at htp_connection_parser.c:198:11 in htp_connection_parser.h
// htp_tx_set_user_data at htp_transaction.c:239:6 in htp_transaction.h
// htp_tx_state_request_start at htp_transaction.c:1084:14 in htp_transaction.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "htp.h"
#include "htp.h"

static htp_connp_t *create_connp() {
    htp_cfg_t *cfg = htp_config_create();
    if (!cfg) return NULL;

    htp_connp_t *connp = htp_connp_create(cfg);
    if (!connp) {
        htp_config_destroy(cfg);
        return NULL;
    }

    return connp;
}

static void destroy_connp(htp_connp_t *connp) {
    if (connp) {
        htp_connp_destroy_all(connp);
    }
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void *)) return 0;

    htp_connp_t *connp = create_connp();
    if (!connp) return 0;

    // Fuzz htp_connp_tx_create
    htp_tx_t *tx = htp_connp_tx_create(connp);
    if (tx) {
        // Fuzz htp_tx_set_user_data
        htp_tx_set_user_data(tx, (void *)Data);
    }

    // Fuzz htp_connp_get_user_data
    void *user_data = htp_connp_get_user_data(connp);
    (void)user_data; // Suppress unused variable warning

    // Fuzz htp_connp_get_out_tx
    htp_tx_t *out_tx = htp_connp_get_out_tx(connp);
    (void)out_tx; // Suppress unused variable warning

    // Fuzz htp_connp_get_in_tx
    htp_tx_t *in_tx = htp_connp_get_in_tx(connp);
    if (in_tx) {
        // Fuzz htp_tx_state_request_start
        htp_status_t status = htp_tx_state_request_start(in_tx);
        (void)status; // Suppress unused variable warning
    }

    destroy_connp(connp);
    return 0;
}