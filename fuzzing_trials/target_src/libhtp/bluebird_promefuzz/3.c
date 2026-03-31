#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/libhtp/htp/bstr.h"
#include "htp/htp.h"
#include "htp/htp.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static void initialize_bstr(bstr *b, const uint8_t *data, size_t len) {
    b->realptr = malloc(len);
    if (b->realptr) {
        memcpy(b->realptr, data, len);
        b->len = len;
        b->size = len;
    } else {
        b->realptr = NULL;
        b->len = 0;
        b->size = 0;
    }
}

static void free_bstr(bstr *b) {
    if (b->realptr) {
        free(b->realptr);
    }
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Test bstr_index_of_mem_nocase
    bstr haystack;
    size_t haystack_len = Size / 2;
    initialize_bstr(&haystack, Data, haystack_len);
    if (haystack.realptr != NULL) {
        int index = bstr_index_of_mem_nocase(&haystack, Data + haystack_len, Size - haystack_len);
        (void)index; // Use or log index as needed
    }

    // Test bstr_util_memdup_to_c
    char *dup_str = bstr_util_memdup_to_c(Data, Size);
    if (dup_str) {
        free(dup_str);
    }

    // Test htp_tx_req_get_param_ex
    htp_tx_t tx;
    memset(&tx, 0, sizeof(htp_tx_t)); // Initialize tx to zero
    if (Size > 0) {
        htp_param_t *param = htp_tx_req_get_param_ex(&tx, HTP_SOURCE_QUERY_STRING, (const char *)Data, Size);
        (void)param; // Use or log param as needed
    }

    // Test bstr_cmp_c_nocasenorzero
    if (haystack.realptr != NULL) {
        // Ensure the Data is null-terminated
        char *null_terminated_data = (char *)malloc(Size + 1);
        if (null_terminated_data) {
            memcpy(null_terminated_data, Data, Size);
            null_terminated_data[Size] = '\0';
            int cmp_result = bstr_cmp_c_nocasenorzero(&haystack, null_terminated_data);
            (void)cmp_result; // Use or log cmp_result as needed
            free(null_terminated_data);
        }
    }

    // Test bstr_index_of_c_nocasenorzero
    if (haystack.realptr != NULL) {
        // Ensure the Data is null-terminated
        char *null_terminated_data = (char *)malloc(Size + 1);
        if (null_terminated_data) {
            memcpy(null_terminated_data, Data, Size);
            null_terminated_data[Size] = '\0';
            int index_c = bstr_index_of_c_nocasenorzero(&haystack, null_terminated_data);
            (void)index_c; // Use or log index_c as needed
            free(null_terminated_data);
        }
    }

    // Test htp_get_version
    char *version = htp_get_version();
    (void)version; // Use or log version as needed

    // Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from htp_get_version to htp_tx_res_process_body_data
    htp_tx_t aunwjrws;
    memset(&aunwjrws, 0, sizeof(aunwjrws));

    htp_status_t ret_htp_tx_res_process_body_data_yhfry = htp_tx_res_process_body_data(&aunwjrws, (const void *)version, 1);

    // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bstr_index_of_mem_nocase to htp_tx_req_set_line
        const bstr gbwojrry;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from htp_tx_res_process_body_data to htp_tx_req_add_param

    htp_status_t ret_htp_tx_req_add_param_cbpct = htp_tx_req_add_param(&aunwjrws, NULL);

    // End mutation: Producer.APPEND_MUTATOR

        memset(&gbwojrry, 0, sizeof(gbwojrry));
        char* ret_bstr_util_strdup_to_c_wbdvt = bstr_util_strdup_to_c(&gbwojrry);
        if (ret_bstr_util_strdup_to_c_wbdvt == NULL){
        	return 0;
        }

        htp_status_t ret_htp_tx_req_set_line_fsllt = htp_tx_req_set_line(NULL, ret_bstr_util_strdup_to_c_wbdvt, (size_t )index, 0);

        // End mutation: Producer.APPEND_MUTATOR

    free_bstr(&haystack);

    return 0;
}