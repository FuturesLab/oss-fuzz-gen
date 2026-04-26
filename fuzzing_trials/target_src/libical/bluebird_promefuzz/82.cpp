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
#include <cassert>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalrecur.h"

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct icalrecurrencetype)) return 0;

    // Prepare a dummy icalrecurrencetype structure
    struct icalrecurrencetype recur;
    memcpy(&recur, Data, sizeof(struct icalrecurrencetype));

    // Initialize the by array to prevent uninitialized access
    for (int i = 0; i < ICAL_BY_NUM_PARTS; ++i) {
        recur.by[i].data = nullptr;
        recur.by[i].size = 0;
    }

    // Ensure rscale is null-terminated and valid
    recur.rscale = nullptr;
    if (Size > sizeof(struct icalrecurrencetype)) {
        size_t rscale_len = Size - sizeof(struct icalrecurrencetype);
        recur.rscale = (char*)malloc(rscale_len + 1);
        if (recur.rscale) {
            memcpy(recur.rscale, Data + sizeof(struct icalrecurrencetype), rscale_len);
            recur.rscale[rscale_len] = '\0';
        }
    }

    // Fuzz icalrecurrencetype_as_string
    char *recur_str = icalrecurrencetype_as_string(&recur);
    // Do not free recur_str as it is managed by libical's internal memory management

    // Fuzz icalrecurrencetype_as_string_r
    char *recur_str_r = icalrecurrencetype_as_string_r(&recur);
    if (recur_str_r) {
        free(recur_str_r); // Assuming the library requires freeing
    }

    // Fuzz icalrecur_freq_to_string with all possible enum values
    for (int i = ICAL_SECONDLY_RECURRENCE; i <= ICAL_NO_RECURRENCE; ++i) {
        const char *freq_str = icalrecur_freq_to_string(static_cast<icalrecurrencetype_frequency>(i));
        if (freq_str) {
            assert(strlen(freq_str) > 0); // Ensure non-empty strings
        }
    }

    // Fuzz icalrecur_string_to_freq with a string from the input
    if (Size > 0) {
        char *input_str = (char*)malloc(Size + 1);
        if (input_str) {
            memcpy(input_str, Data, Size);
            input_str[Size] = '\0';
            icalrecurrencetype_frequency freq = icalrecur_string_to_freq(input_str);
            assert(freq >= ICAL_SECONDLY_RECURRENCE && freq <= ICAL_NO_RECURRENCE);
            free(input_str);
        }
    }

    // Fuzz icalrecur_skip_to_string with all possible enum values
    for (int i = ICAL_SKIP_BACKWARD; i <= ICAL_SKIP_UNDEFINED; ++i) {
        const char *skip_str = icalrecur_skip_to_string(static_cast<icalrecurrencetype_skip>(i));
        if (skip_str) {
            assert(strlen(skip_str) > 0); // Ensure non-empty strings
        }
    }

    // Fuzz icalrecur_string_to_skip with a string from the input
    if (Size > 0) {
        char *input_str = (char*)malloc(Size + 1);
        if (input_str) {
            memcpy(input_str, Data, Size);
            input_str[Size] = '\0';
            icalrecurrencetype_skip skip = icalrecur_string_to_skip(input_str);
            assert(skip >= ICAL_SKIP_BACKWARD && skip <= ICAL_SKIP_UNDEFINED);
            free(input_str);
        }
    }

    // Free dynamically allocated rscale if it was set
    if (recur.rscale) {
        free(recur.rscale);
    }

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

    LLVMFuzzerTestOneInput_82(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
