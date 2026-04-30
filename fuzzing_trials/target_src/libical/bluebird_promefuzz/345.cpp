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
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalparameter.h"

extern "C" int LLVMFuzzerTestOneInput_345(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Convert input data to a null-terminated string
    char *input = (char *)malloc(Size + 1);
    if (!input) return 0; // Handle memory allocation failure
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Create a new icalparameter from the input string
    icalparameter *param = icalparameter_new_from_string(input);
    if (param) {
        // Test icalparameter_as_ical_string_r
        char *icalString = icalparameter_as_ical_string_r(param);
        if (icalString) {
            // Use the resulting string
            printf("%s\n", icalString);
            icalmemory_free_buffer(icalString);
        }

        // Test icalparameter_set_iana_value
        icalparameter_set_iana_value(param, input);
        const char *ianaValue = icalparameter_get_iana_value(param);
        if (ianaValue) {
            printf("%s\n", ianaValue);
        }

        // Test icalparameter_set_xvalue
        icalparameter_set_xvalue(param, input);
        const char *xValue = icalparameter_get_xvalue(param);
        if (xValue) {
            printf("%s\n", xValue);
        }

        // Test icalparameter_set_xname
        icalparameter_set_xname(param, input);
        // Assuming there's a function to get xname, similar to get_xvalue
        // const char *xName = icalparameter_get_xname(param);
        // if (xName) {
        //     printf("%s\n", xName);
        // }

        // Free the parameter
        icalparameter_free(param);
    }

    free(input);
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

    LLVMFuzzerTestOneInput_345(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
