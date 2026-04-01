// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// htp_urldecode_inplace_ex at htp_util.c:1570:14 in htp.h
// htp_urldecode_inplace at htp_util.c:1565:14 in htp.h
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

static bstr *create_bstr_from_input(const uint8_t *Data, size_t Size) {
    size_t len = Size < MAX_BSTR_SIZE ? Size : MAX_BSTR_SIZE;
    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (!b) return NULL;

    b->realptr = (unsigned char *)malloc(len);
    if (!b->realptr) {
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

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    htp_cfg_t *cfg = htp_config_create();
    if (!cfg) return 0;

    bstr *input = create_bstr_from_input(Data, Size);
    if (!input) {
        htp_config_destroy(cfg);
        return 0;
    }

    uint64_t flags = 0;
    int expected_status_code = 0;
    htp_status_t result;

    // Test htp_urldecode_inplace
    result = htp_urldecode_inplace(cfg, HTP_DECODER_URLENCODED, input, &flags);
    if (result == HTP_OK) {
        bstr_adjust_len(input, input->len / 2);
    }

    // Test bstr_to_lowercase
    bstr *lowercase_bstr = bstr_to_lowercase(input);
    if (lowercase_bstr) {
        bstr_adjust_size(lowercase_bstr, lowercase_bstr->size / 2);
    }

    // Test bstr_add_mem_noex
    bstr *appended_bstr = bstr_add_mem_noex(input, Data, Size / 2);
    if (appended_bstr) {
        bstr_adjust_len(appended_bstr, appended_bstr->len);
    }

    // Test htp_urldecode_inplace_ex
    result = htp_urldecode_inplace_ex(cfg, HTP_DECODER_URLENCODED, input, &flags, &expected_status_code);

    free_bstr(input);
    htp_config_destroy(cfg);

    return 0;
}