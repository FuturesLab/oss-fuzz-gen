// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalparameter_decode_value at icalparameter.c:411:6 in icalparameter.h
// icalproperty_get_parameter_as_string_r at icalproperty.c:549:7 in icalproperty.h
// icalproperty_get_parameter_as_string at icalproperty.c:540:13 in icalproperty.h
// icalproperty_set_parameter_from_string at icalproperty.c:507:6 in icalproperty.h
// icalparameter_get_iana_name at icalparameter.c:351:13 in icalparameter.h
// icalparameter_as_ical_string at icalparameter.c:172:7 in icalparameter.h
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
#include <cstdint>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalparameter.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy icalparameter and icalproperty
    icalparameter *param = icalparameter_new(ICAL_ANY_PARAMETER);
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    if (!param || !prop) {
        if (param) icalparameter_free(param);
        if (prop) icalproperty_free(prop);
        return 0;
    }

    // Generate a string from the input data
    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Fuzz icalparameter_get_iana_name
    const char *iana_name = icalparameter_get_iana_name(param);
    if (iana_name) {
        std::cout << "IANA Name: " << iana_name << std::endl;
    }

    // Fuzz icalproperty_get_parameter_as_string_r
    char *param_as_string_r = icalproperty_get_parameter_as_string_r(prop, input.c_str());
    if (param_as_string_r) {
        std::cout << "Parameter as String (r): " << param_as_string_r << std::endl;
        free(param_as_string_r);
    }

    // Fuzz icalproperty_set_parameter_from_string
    icalproperty_set_parameter_from_string(prop, input.c_str(), input.c_str());

    // Fuzz icalparameter_as_ical_string
    char *param_ical_string = icalparameter_as_ical_string(param);
    if (param_ical_string) {
        std::cout << "Parameter as iCal String: " << param_ical_string << std::endl;
    }

    // Fuzz icalparameter_decode_value
    char *mutable_input = strdup(input.c_str());
    if (mutable_input) {
        icalparameter_decode_value(mutable_input);
        std::cout << "Decoded Value: " << mutable_input << std::endl;
        free(mutable_input);
    }

    // Fuzz icalproperty_get_parameter_as_string
    const char *param_as_string = icalproperty_get_parameter_as_string(prop, input.c_str());
    if (param_as_string) {
        std::cout << "Parameter as String: " << param_as_string << std::endl;
    }

    // Cleanup
    icalparameter_free(param);
    icalproperty_free(prop);

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

        LLVMFuzzerTestOneInput_12(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    