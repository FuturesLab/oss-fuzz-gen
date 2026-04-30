// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltriggertype_from_string at icaltypes.c:53:24 in icaltypes.h
// icalparameter_decode_value at icalparameter.c:411:6 in icalparameter.h
// icalvalue_new_from_string at icalvalue.c:780:12 in icalvalue.h
// icalmemory_append_decoded_string at icalmemory.c:519:6 in icalmemory.h
// icalvalue_decode_ical_string at icalvalue.c:1577:6 in icalvalue.h
// icalrecurrencetype_new_from_string at icalrecur.c:818:28 in icalrecur.h
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
#include "icalmemory.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalvalue.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalparameter.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icaltypes.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalrecur.h"

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Convert the input data to a string
    char *inputStr = static_cast<char *>(malloc(Size + 1));
    if (!inputStr) {
        return 0;
    }
    memcpy(inputStr, Data, Size);
    inputStr[Size] = '\0';

    // Ensure the inputStr is null-terminated for functions that expect C-style strings
    if (inputStr[Size - 1] != '\0') {
        inputStr[Size - 1] = '\0';
    }

    // 1. Test icalvalue_new_from_string
    for (int kind = ICAL_ANY_VALUE; kind <= ICAL_XMLREFERENCE_VALUE; ++kind) {
        icalvalue *value = icalvalue_new_from_string(static_cast<icalvalue_kind>(kind), inputStr);
        if (value) {
            icalvalue_free(value);
        }
    }

    // 2. Test icalrecurrencetype_new_from_string
    icalrecurrencetype *recurType = icalrecurrencetype_new_from_string(inputStr);
    if (recurType) {
        free(recurType);
    }

    // 3. Test icaltriggertype_from_string
    icaltriggertype triggerType = icaltriggertype_from_string(inputStr);
    // No need for cleanup as icaltriggertype_from_string does not allocate memory

    // 4. Test icalmemory_append_decoded_string
    char *buf = nullptr;
    char *pos = nullptr;
    size_t buf_size = 0;
    icalmemory_append_decoded_string(&buf, &pos, &buf_size, inputStr);
    if (buf) {
        free(buf);
    }

    // 5. Test icalvalue_decode_ical_string
    if (Size > 0) {
        char decodedText[1024];
        bool success = icalvalue_decode_ical_string(inputStr, decodedText, sizeof(decodedText));
        if (!success) {
            // Handle decoding failure if necessary
        }
    }

    // 6. Test icalparameter_decode_value
    char *mutableStr = strdup(inputStr);
    if (mutableStr) {
        icalparameter_decode_value(mutableStr);
        free(mutableStr);
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

        LLVMFuzzerTestOneInput_46(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    