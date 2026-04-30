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
#include <cstring>
#include <cassert>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalparameter.h"

extern "C" int LLVMFuzzerTestOneInput_167(const uint8_t *Data, size_t Size) {
    // Create a null-terminated string from the input data
    char *inputStr = new char[Size + 1];
    memcpy(inputStr, Data, Size);
    inputStr[Size] = '\0';

    // Test icalparameter_new_from_string
    icalparameter *param = icalparameter_new_from_string(inputStr);
    if (param) {
        // Test icalparameter_get_iana_value
        const char *ianaValue = icalparameter_get_iana_value(param);
        if (ianaValue) {
            std::cout << "IANA Value: " << ianaValue << std::endl;
        }

        // Test icalparameter_as_ical_string_r
        char *icalString = icalparameter_as_ical_string_r(param);
        if (icalString) {
            std::cout << "ICAL String: " << icalString << std::endl;
            icalmemory_free_buffer(icalString);
        }

        // Test icalparameter_set_xname
        icalparameter_set_xname(param, "X-TEST");
        const char *xname = icalparameter_get_xname(param);
        if (xname) {
            std::cout << "X-Name: " << xname << std::endl;
        }

        // Test icalparameter_set_iana_name
        icalparameter_set_iana_name(param, "ROLE");
        const char *ianaName = icalparameter_get_iana_value(param);
        if (ianaName) {
            std::cout << "IANA Name: " << ianaName << std::endl;
        }

        // Clean up
        icalparameter_free(param);
    }

    delete[] inputStr;
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

    LLVMFuzzerTestOneInput_167(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
