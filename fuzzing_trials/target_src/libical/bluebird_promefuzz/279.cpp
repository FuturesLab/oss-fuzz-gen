#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalrecur.h"

extern "C" int LLVMFuzzerTestOneInput_279(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0; // Ensure there's enough data for at least one short

    // Test 1: icalrecurrencetype_day_day_of_week
    short day = *reinterpret_cast<const short*>(Data);
    icalrecurrencetype_weekday weekday = icalrecurrencetype_day_day_of_week(day);

    // Test 2: icalrecurrencetype_month_month
    short month = *reinterpret_cast<const short*>(Data);
    int normalized_month = icalrecurrencetype_month_month(month);

    // Test 3: icalrecurrencetype_new_from_string
    struct icalrecurrencetype *recur = nullptr;
    if (Size > 2) {
        const char *str = reinterpret_cast<const char*>(Data + 2);
        size_t strSize = Size - 2;
        char *strCopy = static_cast<char*>(malloc(strSize + 1));
        if (strCopy) {
            memcpy(strCopy, str, strSize);
            strCopy[strSize] = '\0';
            recur = icalrecurrencetype_new_from_string(strCopy);
            free(strCopy);
        }
    }

    // Test 4: icalrecurrencetype_encode_month
    if (Size > 3) {
        int month_val = Data[2] % 12 + 1; // Ensure month is in the range 1-12
        bool is_leap = Data[3] % 2;
        short encoded_month = icalrecurrencetype_encode_month(month_val, is_leap);
    }

    // Test 5: icalrecurrencetype_as_string_r
    if (recur) {
        char *recur_str = icalrecurrencetype_as_string_r(recur);
        if (recur_str) {
            free(recur_str);
        }
        free(recur);
    }

    // Test 6: icalrecurrencetype_month_is_leap
    bool is_leap_month = icalrecurrencetype_month_is_leap(month);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_279(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
