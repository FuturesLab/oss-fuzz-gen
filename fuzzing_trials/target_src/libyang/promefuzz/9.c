// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_time_tz_offset at tree_data_common.c:1472:1 in tree_data.h
// ly_time_str2ts at tree_data_common.c:1653:1 in tree_data.h
// ly_time_time2str at tree_data_common.c:1622:1 in tree_data.h
// ly_time_str2time at tree_data_common.c:1515:1 in tree_data.h
// ly_time_tz_offset_at at tree_data_common.c:1478:1 in tree_data.h
// ly_time_ts2str at tree_data_common.c:1682:1 in tree_data.h
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
#include "tree_data.h"

static const char *get_dummy_date_time_string(const uint8_t *Data, size_t Size) {
    static char buffer[256];
    size_t len = Size < sizeof(buffer) - 1 ? Size : sizeof(buffer) - 1;
    memcpy(buffer, Data, len);
    buffer[len] = '\0';
    return buffer;
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
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
    if (str) {
        free(str);
    }

    return 0;
}