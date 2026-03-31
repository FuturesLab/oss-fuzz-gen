#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htp/htp.h"

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

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
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