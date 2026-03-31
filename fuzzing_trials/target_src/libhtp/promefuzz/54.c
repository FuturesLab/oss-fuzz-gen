// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// htp_tx_req_get_param at htp_transaction.c:254:14 in htp_transaction.h
// htp_tx_req_get_param_ex at htp_transaction.c:259:14 in htp_transaction.h
// htp_connp_get_out_tx at htp_connection_parser.c:157:11 in htp_connection_parser.h
// htp_tx_create at htp_transaction.c:56:11 in htp_transaction.h
// htp_tx_req_set_method_number at htp_transaction.c:323:6 in htp_transaction.h
// htp_tx_state_request_headers at htp_transaction.c:1098:14 in htp_transaction.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htp.h"
#include "htp.h"

static htp_tx_t *create_dummy_transaction(htp_connp_t *connp) {
    return htp_tx_create(connp);
}

static void fuzz_htp_tx_req_get_param(htp_tx_t *tx, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        htp_param_t *param = htp_tx_req_get_param(tx, (const char *)Data, Size);
        (void)param; // Suppress unused variable warning
    }
}

static void fuzz_htp_tx_req_set_method_number(htp_tx_t *tx, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        enum htp_method_t method_number = (enum htp_method_t)(Data[0] % HTP_M_INVALID);
        htp_tx_req_set_method_number(tx, method_number);
    }
}

static void fuzz_htp_connp_get_out_tx(htp_connp_t *connp) {
    htp_tx_t *tx = htp_connp_get_out_tx(connp);
    (void)tx; // Suppress unused variable warning
}

static void fuzz_htp_tx_req_get_param_ex(htp_tx_t *tx, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        enum htp_data_source_t source = (enum htp_data_source_t)(Data[0] % 4);
        htp_param_t *param = htp_tx_req_get_param_ex(tx, source, (const char *)Data, Size);
        (void)param; // Suppress unused variable warning
    }
}

static void fuzz_htp_tx_state_request_headers(htp_tx_t *tx) {
    if (tx) {
        htp_status_t status = htp_tx_state_request_headers(tx);
        (void)status; // Suppress unused variable warning
    }
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) return 0;

    htp_connp_t *connp = htp_connp_create(cfg);
    if (connp == NULL) {
        htp_config_destroy(cfg);
        return 0;
    }

    htp_tx_t *tx = create_dummy_transaction(connp);
    if (tx == NULL) {
        htp_connp_destroy_all(connp);
        htp_config_destroy(cfg);
        return 0;
    }

    fuzz_htp_tx_req_get_param(tx, Data, Size);
    fuzz_htp_tx_req_set_method_number(tx, Data, Size);
    fuzz_htp_connp_get_out_tx(connp);
    fuzz_htp_tx_req_get_param_ex(tx, Data, Size);
    fuzz_htp_tx_state_request_headers(tx);

    htp_connp_destroy_all(connp);
    htp_config_destroy(cfg);
    return 0;
}