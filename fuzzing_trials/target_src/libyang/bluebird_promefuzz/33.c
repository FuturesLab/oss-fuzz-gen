#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"

static const char *get_dummy_date_time_string(const uint8_t *Data, size_t Size) {
    static char buffer[256];
    size_t len = Size < sizeof(buffer) - 1 ? Size : sizeof(buffer) - 1;
    memcpy(buffer, Data, len);
    buffer[len] = '\0';
    return buffer;
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Test ly_time_tz_offset
    int offset = ly_time_tz_offset();

    // Test ly_time_str2ts
    struct timespec ts;
    const char *datetime_str = get_dummy_date_time_string(Data, Size);
    LY_ERR err = ly_time_str2ts(datetime_str, &ts);

    // Test ly_time_time2str
    char *str = NULL;
    time_t current_time = time(NULL);
    err = ly_time_time2str(current_time, datetime_str, &str);
    if (str) {
        free(str);
    }

    // Test ly_time_str2time
    time_t time_val;
    char *fractions_s = NULL;
    err = ly_time_str2time(datetime_str, &time_val, &fractions_s);
    if (fractions_s) {
        free(fractions_s);
    }

    // Test ly_time_tz_offset_at

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_time_str2time to lyd_path

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_get_options with ly_ctx_internal_modules_count
    uint32_t ret_ly_ctx_get_options_rjsct = ly_ctx_internal_modules_count(NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_ly_ctx_get_options_rjsct < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_internal_modules_count to lyd_compare_single
    struct lyd_node* ret_lyd_child_no_keys_txvvw = lyd_child_no_keys(NULL);
    if (ret_lyd_child_no_keys_txvvw == NULL){
    	return 0;
    }
    struct lyd_node zjddprlk;
    memset(&zjddprlk, 0, sizeof(zjddprlk));
    lyd_free_siblings(&zjddprlk);

    LY_ERR ret_lyd_compare_single_googo = lyd_compare_single(ret_lyd_child_no_keys_txvvw, &zjddprlk, ret_ly_ctx_get_options_rjsct);

    // End mutation: Producer.APPEND_MUTATOR

    char* ret_lyd_path_loxba = lyd_path(NULL, 0, fractions_s, (size_t )ret_ly_ctx_get_options_rjsct);
    if (ret_lyd_path_loxba == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int offset_at = ly_time_tz_offset_at(current_time);

    // Test ly_time_ts2str
    str = NULL;
    err = ly_time_ts2str(&ts, &str);
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_time_ts2str to ly_ctx_new_printed


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ly_ctx_new_printed
    LY_ERR ret_ly_ctx_new_printed_noyuk = ly_ctx_new_printed((const void *)Data, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

;
    if (str) {
        free(str);
    }

    return 0;
}