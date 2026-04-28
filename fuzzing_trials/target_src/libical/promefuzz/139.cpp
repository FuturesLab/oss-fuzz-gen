// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalrecur_string_to_skip at icalrecur.c:224:25 in icalrecur.h
// icalrecur_skip_to_string at icalrecur.c:236:13 in icalrecur.h
// icalrecur_freq_to_string at icalrecur.c:203:13 in icalrecur.h
// icalrecur_string_to_freq at icalrecur.c:191:30 in icalrecur.h
// icalrecur_weekday_to_string at icalrecur.c:261:13 in icalrecur.h
// icalrecurrencetype_as_string_r at icalrecur.c:1002:7 in icalrecur.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalrecur.h"

static void fuzz_icalrecur_weekday_to_string(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalrecurrencetype_weekday)) return;
    icalrecurrencetype_weekday weekday;
    memcpy(&weekday, Data, sizeof(icalrecurrencetype_weekday));
    icalrecur_weekday_to_string(weekday);
}

static void fuzz_icalrecur_freq_to_string(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalrecurrencetype_frequency)) return;
    icalrecurrencetype_frequency freq;
    memcpy(&freq, Data, sizeof(icalrecurrencetype_frequency));
    icalrecur_freq_to_string(freq);
}

static void fuzz_icalrecur_string_to_freq(const uint8_t *Data, size_t Size) {
    char str[Size + 1];
    memcpy(str, Data, Size);
    str[Size] = '\0';
    icalrecur_string_to_freq(str);
}

static void fuzz_icalrecur_skip_to_string(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalrecurrencetype_skip)) return;
    icalrecurrencetype_skip skip;
    memcpy(&skip, Data, sizeof(icalrecurrencetype_skip));
    icalrecur_skip_to_string(skip);
}

static void fuzz_icalrecurrencetype_as_string_r(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalrecurrencetype)) return;
    icalrecurrencetype recur;
    memcpy(&recur, Data, sizeof(icalrecurrencetype));

    // Ensure rscale is null-terminated and valid
    recur.rscale = nullptr;
    if (Size > sizeof(icalrecurrencetype)) {
        size_t rscale_len = Size - sizeof(icalrecurrencetype);
        recur.rscale = (char*)malloc(rscale_len + 1);
        if (recur.rscale) {
            memcpy(recur.rscale, Data + sizeof(icalrecurrencetype), rscale_len);
            recur.rscale[rscale_len] = '\0';
        }
    }

    // Initialize the 'by' array data pointers to avoid invalid memory access
    for (int i = 0; i < ICAL_BY_NUM_PARTS; ++i) {
        recur.by[i].data = nullptr;
        recur.by[i].size = 0;
    }

    char *result = icalrecurrencetype_as_string_r(&recur);
    if (result) {
        free(result);
    }

    if (recur.rscale) {
        free(recur.rscale);
    }
}

static void fuzz_icalrecur_string_to_skip(const uint8_t *Data, size_t Size) {
    char str[Size + 1];
    memcpy(str, Data, Size);
    str[Size] = '\0';
    icalrecur_string_to_skip(str);
}

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *Data, size_t Size) {
    fuzz_icalrecur_weekday_to_string(Data, Size);
    fuzz_icalrecur_freq_to_string(Data, Size);
    fuzz_icalrecur_string_to_freq(Data, Size);
    fuzz_icalrecur_skip_to_string(Data, Size);
    fuzz_icalrecurrencetype_as_string_r(Data, Size);
    fuzz_icalrecur_string_to_skip(Data, Size);
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

        LLVMFuzzerTestOneInput_139(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    