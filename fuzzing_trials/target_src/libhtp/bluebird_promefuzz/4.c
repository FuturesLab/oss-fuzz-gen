#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libhtp/htp/bstr.h"

static bstr *create_bstr(const uint8_t *Data, size_t Size) {
    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (!b) {
        return NULL;
    }

    b->len = Size;
    b->size = Size;
    b->realptr = (unsigned char *)malloc(Size);
    if (!b->realptr) {
        free(b);
        return NULL;
    }

    memcpy(b->realptr, Data, Size);
    return b;
}

static void free_bstr(bstr *b) {
    if (b) {
        if (b->realptr) {
            free(b->realptr);
        }
        free(b);
    }
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    bstr *b = create_bstr(Data, Size);
    if (!b) {
        return 0;
    }

    // Fuzz bstr_char_at
    size_t pos = Data[0] % Size;
    int char_at_result = bstr_char_at(b, pos);

    // Fuzz bstr_cmp_mem_nocase
    int cmp_mem_nocase_result = bstr_cmp_mem_nocase(b, Data, Size);

    // Fuzz bstr_begins_with_mem
    int begins_with_mem_result = bstr_begins_with_mem(b, Data, Size);

    // Fuzz bstr_begins_with_mem_nocase
    int begins_with_mem_nocase_result = bstr_begins_with_mem_nocase(b, Data, Size);

    // Fuzz bstr_cmp_c_nocase
    char cstr[] = "fuzz";
    int cmp_c_nocase_result = bstr_cmp_c_nocase(b, cstr);

    // Fuzz bstr_begins_with
    bstr *bneedle = create_bstr(Data, Size / 2);
    if (bneedle) {
        int begins_with_result = bstr_begins_with(b, bneedle);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bstr_begins_with to htp_tx_res_set_status_message
        void* ret_htp_tx_get_user_data_rcxuh = htp_tx_get_user_data(NULL);
        if (ret_htp_tx_get_user_data_rcxuh == NULL){
        	return 0;
        }

        htp_status_t ret_htp_tx_res_set_status_message_mhyma = htp_tx_res_set_status_message(NULL, (const char *)ret_htp_tx_get_user_data_rcxuh, (size_t )begins_with_result, 0);

        // End mutation: Producer.APPEND_MUTATOR

        free_bstr(bneedle);
    }

    free_bstr(b);
    return 0;
}