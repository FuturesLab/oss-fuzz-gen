// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalparameter_free at icalparameter.c:51:6 in icalparameter.h
// icalparameter_clone at icalparameter.c:79:16 in icalparameter.h
// icallangbind_get_first_parameter at icallangbind.c:39:16 in icallangbind.h
// icalproperty_add_parameter at icalproperty.c:480:6 in icalproperty.h
// icalparameter_set_parent at icalparameter.c:356:6 in icalproperty.h
// icalproperty_set_parameter at icalproperty.c:488:6 in icalproperty.h
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
#include <cstring>
#include <cstdint>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icallangbind.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalparameter.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

static icalparameter* createParameterFromData(const uint8_t *Data, size_t Size) {
    if (Size == 0) return nullptr;
    std::string paramString(reinterpret_cast<const char*>(Data), Size);
    return icalparameter_new_from_string(paramString.c_str());
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    // Create an icalparameter from input data
    icalparameter *param = createParameterFromData(Data, Size);
    if (!param) return 0;

    // Clone the parameter
    icalparameter *clone = icalparameter_clone(param);

    // Create a dummy icalproperty
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);

    // Add parameter to property
    if (property) {
        icalproperty_add_parameter(property, param);

        // Set the parameter's parent
        icalparameter_set_parent(param, property);

        // Set the parameter for the property
        icalproperty_set_parameter(property, param);

        // Retrieve the first parameter
        icalparameter *firstParam = icallangbind_get_first_parameter(property);
        if (firstParam) {
            // Clone the first parameter for further testing
            icalparameter *firstParamClone = icalparameter_clone(firstParam);
            if (firstParamClone) {
                icalparameter_free(firstParamClone);
            }
        }

        // Clean up property
        icalproperty_free(property);
    }

    // Free the cloned parameter
    if (clone) {
        icalparameter_free(clone);
    }

    // Free the original parameter
    icalparameter_free(param);

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

        LLVMFuzzerTestOneInput_2(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    