// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// htp_get_version at htp_util.c:2543:7 in htp.h
// bstr_util_memdup_to_c at bstr.c:589:7 in bstr.h
// htp_tx_req_get_param_ex at htp_transaction.c:259:14 in htp_transaction.h
// bstr_index_of_c_nocasenorzero at bstr.c:302:5 in bstr.h
// bstr_index_of_mem_nocase at bstr.c:310:5 in bstr.h
// bstr_cmp_c_nocasenorzero at bstr.c:222:5 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstr.h"
#include "htp.h"
#include "htp.h"

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

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

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
    free_bstr(&haystack);

    return 0;
}