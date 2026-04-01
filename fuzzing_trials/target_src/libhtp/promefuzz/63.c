// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// htp_urldecode_inplace at htp_util.c:1565:14 in htp.h
// htp_urldecode_inplace_ex at htp_util.c:1570:14 in htp.h
// bstr_add_mem_noex at bstr.c:81:7 in bstr.h
// bstr_adjust_len at bstr.c:102:6 in bstr.h
// bstr_to_lowercase at bstr.c:334:7 in bstr.h
// bstr_adjust_size at bstr.c:110:6 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bstr.h"
#include "htp.h"

#define MAX_BSTR_SIZE 1024

static bstr *create_random_bstr(const uint8_t *Data, size_t Size) {
    size_t len = Size < MAX_BSTR_SIZE ? Size : MAX_BSTR_SIZE;
    bstr *b = malloc(sizeof(bstr));
    if (b == NULL) return NULL;
    b->realptr = malloc(len);
    if (b->realptr == NULL) {
        free(b);
        return NULL;
    }
    memcpy(b->realptr, Data, len);
    b->len = len;
    b->size = len;
    return b;
}

static void free_bstr(bstr *b) {
    if (b) {
        free(b->realptr);
        free(b);
    }
}

int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a minimal htp_cfg_t structure
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) return 0;

    enum htp_decoder_ctx_t ctx = HTP_DECODER_URLENCODED;

    uint64_t flags = 0;
    int expected_status_code = 0;

    bstr *input = create_random_bstr(Data, Size);
    if (input == NULL) {
        htp_config_destroy(cfg);
        return 0;
    }

    // Test htp_urldecode_inplace
    htp_status_t status = htp_urldecode_inplace(cfg, ctx, input, &flags);
    if (status == HTP_OK) {
        // Test bstr_adjust_len
        size_t newlen = input->len > 0 ? input->len - 1 : 0;
        bstr_adjust_len(input, newlen);

        // Test bstr_to_lowercase
        bstr *lowercase_bstr = bstr_to_lowercase(input);
        if (lowercase_bstr != NULL) {
            // Test bstr_add_mem_noex
            bstr_add_mem_noex(lowercase_bstr, Data, Size > 10 ? 10 : Size);
        }
    }

    // Test htp_urldecode_inplace_ex
    htp_urldecode_inplace_ex(cfg, ctx, input, &flags, &expected_status_code);

    // Test bstr_adjust_size
    bstr_adjust_size(input, input->size > 0 ? input->size - 1 : 0);

    free_bstr(input);
    htp_config_destroy(cfg);
    return 0;
}