// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_util_strdup_to_c at bstr.c:621:7 in bstr.h
// bstr_dup_c at bstr.c:242:7 in bstr.h
// htp_tx_create at htp_transaction.c:56:11 in htp_transaction.h
// bstr_dup_mem at bstr.c:258:7 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstr.h"
#include "htp.h"
#include "htp.h"

static htp_connp_t *create_dummy_connp() {
    htp_cfg_t *cfg = htp_config_create();
    if (!cfg) {
        return NULL;
    }

    htp_connp_t *connp = htp_connp_create(cfg);
    if (!connp) {
        htp_config_destroy(cfg);
        return NULL;
    }

    return connp;
}

static void destroy_dummy_connp(htp_connp_t *connp) {
    if (connp) {
        htp_connp_destroy_all(connp);
    }
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    htp_connp_t *connp = create_dummy_connp();
    if (!connp) return 0;

    htp_tx_t *tx = htp_tx_create(connp);
    if (!tx) {
        destroy_dummy_connp(connp);
        return 0;
    }

    char *cstr = (char *)malloc(Size + 1);
    if (!cstr) {
        destroy_dummy_connp(connp);
        return 0;
    }
    memcpy(cstr, Data, Size);
    cstr[Size] = '\0';

    bstr *bstr1 = bstr_dup_c(cstr);
    bstr *bstr2 = bstr_dup_c(cstr);
    char *dup_cstr = bstr_util_strdup_to_c(bstr1);

    if (bstr1) bstr_free(bstr1);
    if (bstr2) bstr_free(bstr2);
    free(dup_cstr);
    free(cstr);

    // No need to free tx, as htp_tx_create is managed by connp and will be freed by htp_connp_destroy_all
    tx = htp_tx_create(connp);
    if (!tx) {
        destroy_dummy_connp(connp);
        return 0;
    }

    bstr1 = bstr_dup_mem(Data, Size);
    bstr2 = bstr_dup_mem(Data, Size);
    dup_cstr = bstr_util_strdup_to_c(bstr1);

    if (bstr1) bstr_free(bstr1);
    if (bstr2) bstr_free(bstr2);
    free(dup_cstr);

    destroy_dummy_connp(connp);
    return 0;
}