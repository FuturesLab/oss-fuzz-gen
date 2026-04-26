// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_action_to_string at icalderivedproperty.c:7274:13 in icalproperty.h
// icalproperty_string_to_action at icalderivedproperty.c:7282:21 in icalproperty.h
// icalproperty_participanttype_to_string at icalderivedproperty.c:7358:13 in icalproperty.h
// icalproperty_transp_to_string at icalderivedproperty.c:7302:13 in icalproperty.h
// icalproperty_method_to_string at icalderivedproperty.c:7218:13 in icalproperty.h
// icalproperty_class_to_string at icalderivedproperty.c:7330:13 in icalproperty.h
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
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz icalproperty_class_to_string
    icalproperty_class cls = static_cast<icalproperty_class>(Data[0] % (ICAL_CLASS_NONE + 1));
    const char *class_str = icalproperty_class_to_string(cls);

    // Fuzz icalproperty_transp_to_string
    icalproperty_transp transp = static_cast<icalproperty_transp>(Data[0] % (ICAL_TRANSP_NONE + 1));
    const char *transp_str = icalproperty_transp_to_string(transp);

    // Fuzz icalproperty_participanttype_to_string
    icalproperty_participanttype part_type = static_cast<icalproperty_participanttype>(Data[0] % (ICAL_PARTICIPANTTYPE_NONE + 1));
    const char *part_type_str = icalproperty_participanttype_to_string(part_type);

    // Fuzz icalproperty_action_to_string
    icalproperty_action action = static_cast<icalproperty_action>(Data[0] % (ICAL_ACTION_NONE + 1));
    const char *action_str = icalproperty_action_to_string(action);

    // Fuzz icalproperty_method_to_string
    icalproperty_method method = static_cast<icalproperty_method>(Data[0] % (ICAL_METHOD_NONE + 1));
    const char *method_str = icalproperty_method_to_string(method);

    // Fuzz icalproperty_string_to_action
    char string_buffer[256];
    size_t copy_size = Size < sizeof(string_buffer) - 1 ? Size : sizeof(string_buffer) - 1;
    memcpy(string_buffer, Data, copy_size);
    string_buffer[copy_size] = '\0'; // Ensure null-termination
    icalproperty_action action_from_string = icalproperty_string_to_action(string_buffer);

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

        LLVMFuzzerTestOneInput_98(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    