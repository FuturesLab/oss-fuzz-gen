// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// htp_connp_create at htp_connection_parser.c:77:14 in htp_connection_parser.h
// bstr_util_strdup_to_c at bstr.c:621:7 in bstr.h
// htp_tx_create at htp_transaction.c:56:11 in htp_transaction.h
// bstr_free at bstr.c:285:6 in bstr.h
// bstr_dup_c at bstr.c:242:7 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <bstr.h>
#include "htp.h"
#include "htp.h"

#define MIN_SIZE 64

static void fuzz_bstr_operations(const char *cstr, size_t cstr_size) {
    if (cstr == NULL || cstr_size == 0) return;

    // Ensure the input is null-terminated for safety
    char *safe_cstr = (char *)malloc(cstr_size + 1);
    if (!safe_cstr) return;
    memcpy(safe_cstr, cstr, cstr_size);
    safe_cstr[cstr_size] = '\0';

    bstr *b = bstr_dup_c(safe_cstr);
    if (b != NULL) {
        char *cstr_dup1 = bstr_util_strdup_to_c(b);
        char *cstr_dup2 = bstr_util_strdup_to_c(b);
        if (cstr_dup1) free(cstr_dup1);
        if (cstr_dup2) free(cstr_dup2);
        bstr_free(b);
    }

    free(safe_cstr);
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < MIN_SIZE) return 0;

    htp_cfg_t *cfg = (htp_cfg_t *)malloc(MIN_SIZE);
    if (cfg == NULL) return 0;

    memcpy(cfg, Data, MIN_SIZE);
    htp_connp_t *connp = htp_connp_create(cfg);
    if (connp == NULL) {
        free(cfg);
        return 0;
    }

    htp_tx_t *tx = htp_tx_create(connp);
    if (tx == NULL) {
        htp_connp_destroy_all(connp);
        free(cfg);
        return 0;
    }

    const char *cstr = (const char *)Data + MIN_SIZE;
    size_t cstr_size = Size - MIN_SIZE;

    if (cstr_size > 0) {
        fuzz_bstr_operations(cstr, cstr_size);
        fuzz_bstr_operations(cstr, cstr_size);
        fuzz_bstr_operations(cstr, cstr_size);
        fuzz_bstr_operations(cstr, cstr_size);
        fuzz_bstr_operations(cstr, cstr_size);
    }

    htp_connp_destroy_all(connp);
    free(cfg);
    return 0;
}