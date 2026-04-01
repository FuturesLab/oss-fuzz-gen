// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// htp_tx_req_set_protocol_number at htp_transaction.c:346:6 in htp_transaction.h
// htp_tx_state_request_complete at htp_transaction.c:1053:14 in htp_transaction.h
// htp_tx_state_response_line at htp_transaction.c:728:14 in htp_transaction.h
// htp_tx_state_request_headers at htp_transaction.c:1098:14 in htp_transaction.h
// htp_tx_req_set_headers_clear at htp_transaction.c:654:14 in htp_transaction.h
// htp_tx_state_request_start at htp_transaction.c:1084:14 in htp_transaction.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htp.h"

static htp_tx_t* create_transaction() {
    htp_tx_t *tx = (htp_tx_t *)malloc(sizeof(htp_tx_t));
    if (tx != NULL) {
        memset(tx, 0, sizeof(htp_tx_t));
    }
    return tx;
}

static void destroy_transaction(htp_tx_t *tx) {
    if (tx != NULL) {
        free(tx);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    htp_tx_t *tx = create_transaction();
    if (tx == NULL) {
        return 0;
    }

    // Fuzz htp_tx_req_set_headers_clear
    htp_status_t status = htp_tx_req_set_headers_clear(tx);
    if (status != HTP_OK) {
        destroy_transaction(tx);
        return 0;
    }

    // Fuzz htp_tx_req_set_protocol_number with random protocol number
    int protocol_number = Size > 0 ? Data[0] : 0;
    htp_tx_req_set_protocol_number(tx, protocol_number);

    // Fuzz htp_tx_state_request_complete
    status = htp_tx_state_request_complete(tx);
    if (status != HTP_OK && status != HTP_STOP) {
        destroy_transaction(tx);
        return 0;
    }

    // Fuzz htp_tx_state_request_start
    status = htp_tx_state_request_start(tx);
    if (status != HTP_OK && status != HTP_STOP) {
        destroy_transaction(tx);
        return 0;
    }

    // Fuzz htp_tx_state_response_line
    status = htp_tx_state_response_line(tx);
    if (status != HTP_OK && status != HTP_STOP) {
        destroy_transaction(tx);
        return 0;
    }

    // Fuzz htp_tx_state_request_headers
    status = htp_tx_state_request_headers(tx);
    if (status != HTP_OK && status != HTP_STOP) {
        destroy_transaction(tx);
        return 0;
    }

    destroy_transaction(tx);
    return 0;
}