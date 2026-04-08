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

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
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