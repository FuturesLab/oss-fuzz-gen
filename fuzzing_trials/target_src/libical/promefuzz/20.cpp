// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalparameter_new at icalparameter.c:44:16 in icalparameter.h
// icalparameter_isa at icalparameter.c:272:20 in icalparameter.h
// icalparameter_new_from_value_string at icalderivedparameter.c:3011:16 in icalparameter.h
// icalparameter_free at icalparameter.c:51:6 in icalparameter.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalparameter.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"
}

static void fuzz_icalparameter_new_from_value_string(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    icalparameter_kind kind = static_cast<icalparameter_kind>(Data[0]);
    size_t value_size = Size - 1;
    char *value = static_cast<char *>(malloc(value_size + 1));
    if (!value) return;

    memcpy(value, Data + 1, value_size);
    value[value_size] = '\0';

    icalparameter *param = icalparameter_new_from_value_string(kind, value);
    if (param) {
        icalparameter_free(param);
    }

    free(value);
}

static void fuzz_icalparameter_new(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    icalparameter_kind kind = static_cast<icalparameter_kind>(Data[0]);

    icalparameter *param = icalparameter_new(kind);
    if (param) {
        icalparameter_free(param);
    }
}

static void fuzz_icalparameter_isa(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    icalparameter_kind kind = static_cast<icalparameter_kind>(Data[0]);
    icalparameter *param = icalparameter_new(kind);
    if (param) {
        icalparameter_kind result_kind = icalparameter_isa(param);
        (void)result_kind; // Suppress unused variable warning
        icalparameter_free(param);
    }
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    fuzz_icalparameter_new_from_value_string(Data, Size);
    fuzz_icalparameter_new(Data, Size);
    fuzz_icalparameter_isa(Data, Size);

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

        LLVMFuzzerTestOneInput_20(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    