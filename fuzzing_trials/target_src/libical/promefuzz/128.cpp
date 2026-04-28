// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalrecur_resize_by at icalrecur.c:296:6 in icalrecur.h
// icalrecurrencetype_encode_month at icalrecur.c:4135:7 in icalrecur.h
// icallangbind_quote_as_ical_r at icallangbind.c:282:7 in icallangbind.h
// icalrecurrencetype_unref at icalrecur.c:739:6 in icalrecur.h
// icalrecurrencetype_new_from_string at icalrecur.c:818:28 in icalrecur.h
// icalrecurrencetype_as_string at icalrecur.c:993:7 in icalrecur.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icallangbind.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalrecur.h"

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a null-terminated string from the input data
    char *inputStr = static_cast<char*>(malloc(Size + 1));
    if (!inputStr) return 0;
    memcpy(inputStr, Data, Size);
    inputStr[Size] = '\0';

    // Test icalrecurrencetype_new_from_string
    struct icalrecurrencetype *recur = icalrecurrencetype_new_from_string(inputStr);
    if (recur) {
        // Test icalrecurrencetype_as_string
        char *recurStr = icalrecurrencetype_as_string(recur);
        if (recurStr) {
            free(recurStr); // Assuming the library uses malloc/calloc for allocation
        }

        // Test icalrecurrencetype_unref
        icalrecurrencetype_unref(recur);
    }

    // Test icalrecurrencetype_encode_month
    if (Size >= 2) { // Ensure we have enough data
        int month = Data[0] % 12 + 1; // Ensure month is between 1 and 12
        bool is_leap = Data[1] % 2 == 0;
        short encodedMonth = icalrecurrencetype_encode_month(month, is_leap);
        (void)encodedMonth; // Use variable to avoid unused variable warning
    }

    // Test icallangbind_quote_as_ical_r
    char *quotedStr = icallangbind_quote_as_ical_r(inputStr);
    if (quotedStr) {
        free(quotedStr); // Assuming the library uses malloc/calloc for allocation
    }

    // Test icalrecur_resize_by
    if (Size >= 4) { // Ensure we have enough data
        short newSize = static_cast<short>((Data[2] << 8) | Data[3]);
        icalrecurrence_by_data byData = {nullptr, 0};
        bool resizeResult = icalrecur_resize_by(&byData, newSize);
        (void)resizeResult; // Use variable to avoid unused variable warning
        if (byData.data) {
            free(byData.data); // Free allocated data if any
        }
    }

    free(inputStr);
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

        LLVMFuzzerTestOneInput_128(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    