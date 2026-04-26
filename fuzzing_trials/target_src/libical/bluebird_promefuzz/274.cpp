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
#include "/src/libical/src/libical/icalmemory.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalvalue.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalparameter.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icaltypes.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalrecur.h"

extern "C" int LLVMFuzzerTestOneInput_274(const uint8_t *Data, size_t Size) {
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
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalvalue_decode_ical_string to icalparameter_set_iana
        icalparameter* ret_icalparameter_new_response_ymbsc = icalparameter_new_response(ICAL_PATCH_VERSION);
        if (ret_icalparameter_new_response_ymbsc == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_icalparameter_new_response_ymbsc) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!decodedText) {
        	return 0;
        }
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalparameter_set_iana with icalparameter_remove_delegatedto
        icalparameter_remove_delegatedto(ret_icalparameter_new_response_ymbsc, decodedText);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
        // End mutation: Producer.APPEND_MUTATOR
        
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_274(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
