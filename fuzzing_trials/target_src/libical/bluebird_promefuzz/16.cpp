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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalparameter.h"

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a dummy string from the input data
    char *inputString = static_cast<char *>(malloc(Size + 1));
    if (!inputString) {
        return 0;
    }
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Create an icalparameter from the input string
    icalparameter *param = icalparameter_new_from_string(inputString);
    if (param) {
        // Test icalparameter_clone
        icalparameter *clone = icalparameter_clone(param);
        if (clone) {
            icalparameter_free(clone);
        }

        // Test icalparameter_is_multivalued
        bool isMultivalued = icalparameter_is_multivalued(param);

        // Test icalparameter_kind_is_valid
        icalparameter_kind kind = icalparameter_isa(param);
        bool isValidKind = icalparameter_kind_is_valid(kind);

        // Test icalparameter_has_same_name
        bool hasSameName = icalparameter_has_same_name(param, param);

        // Test icalparameter_isa_parameter
        bool isAParameter = icalparameter_isa_parameter(param);

        // Free the icalparameter
        icalparameter_free(param);
    }

    free(inputString);
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

    LLVMFuzzerTestOneInput_16(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
