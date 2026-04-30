// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalrecur_iterator_free at icalrecur.c:2371:6 in icalrecur.h
// icalrecur_iterator_new at icalrecur.c:2245:21 in icalrecur.h
// icalrecur_iterator_next at icalrecur.c:3580:21 in icalrecur.h
// icalrecur_iterator_prev at icalrecur.c:3703:21 in icalrecur.h
// icalrecur_iterator_set_range at icalrecur.c:4022:6 in icalrecur.h
// icalrecur_iterator_set_end at icalrecur.c:4011:6 in icalrecur.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalrecur.h"

static icaltimetype create_icaltimetype(int year) {
    icaltimetype tt;
    memset(&tt, 0, sizeof(tt));
    tt.year = year;
    return tt;
}

static icalrecurrencetype* create_icalrecurrencetype() {
    icalrecurrencetype* rule = new icalrecurrencetype;
    memset(rule, 0, sizeof(icalrecurrencetype));
    return rule;
}

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    int year = *reinterpret_cast<const int*>(Data);
    Data += 4;
    Size -= 4;

    icalrecurrencetype *rule = create_icalrecurrencetype();
    icaltimetype dtstart = create_icaltimetype(year);

    icalrecur_iterator *iterator = icalrecur_iterator_new(rule, dtstart);
    if (iterator) {
        icaltimetype end = create_icaltimetype(year + 1);
        icalrecur_iterator_set_end(iterator, end);

        icaltimetype from = create_icaltimetype(year);
        icaltimetype to = create_icaltimetype(year + 2);
        icalrecur_iterator_set_range(iterator, from, to);

        icaltimetype next_occurrence = icalrecur_iterator_next(iterator);
        icaltimetype prev_occurrence = icalrecur_iterator_prev(iterator);

        icalrecur_iterator_free(iterator);
    }

    delete rule;
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

        LLVMFuzzerTestOneInput_154(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    