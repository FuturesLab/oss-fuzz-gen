// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalrecurrencetype_day_position at icalrecur.c:4107:5 in icalrecur.h
// icalrecurrencetype_encode_day at icalrecur.c:4118:7 in icalrecur.h
// icalrecurrencetype_day_day_of_week at icalrecur.c:4102:33 in icalrecur.h
// icalrecur_string_to_weekday at icalrecur.c:274:28 in icalrecur.h
// icalrecurrencetype_new_from_string at icalrecur.c:818:28 in icalrecur.h
// icalrecur_weekday_to_string at icalrecur.c:261:13 in icalrecur.h
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
#include <cstdio>
#include <cstring>
#include <string>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalrecur.h"

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz icalrecurrencetype_day_day_of_week
    short day_value = static_cast<short>(Data[0]);
    icalrecurrencetype_weekday weekday = icalrecurrencetype_day_day_of_week(day_value);

    // Fuzz icalrecur_string_to_weekday
    std::string str(reinterpret_cast<const char*>(Data), Size);
    icalrecurrencetype_weekday weekday_from_str = icalrecur_string_to_weekday(str.c_str());

    // Fuzz icalrecurrencetype_day_position
    int position = icalrecurrencetype_day_position(day_value);

    // Fuzz icalrecurrencetype_new_from_string
    struct icalrecurrencetype *recur_type = icalrecurrencetype_new_from_string(str.c_str());
    if (recur_type) {
        // Assuming there's a function to free the recurrence type, which is typical for C libraries
        // free_icalrecurrencetype(recur_type); // Uncomment if such a function exists
    }

    // Fuzz icalrecurrencetype_encode_day
    for (int pos = -3; pos <= 3; ++pos) {
        for (int wd = ICAL_NO_WEEKDAY; wd <= ICAL_SATURDAY_WEEKDAY; ++wd) {
            short encoded_day = icalrecurrencetype_encode_day(static_cast<icalrecurrencetype_weekday>(wd), pos);
        }
    }

    // Fuzz icalrecur_weekday_to_string
    const char *weekday_str = icalrecur_weekday_to_string(weekday);

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

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_121(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    