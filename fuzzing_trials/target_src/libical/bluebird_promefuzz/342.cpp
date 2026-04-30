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
#include <fstream>
#include <string>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalproperty.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalvalue.h"

extern "C" int LLVMFuzzerTestOneInput_342(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // 1. Fuzz icalproperty_participanttype_to_string
    icalproperty_participanttype participant_type = static_cast<icalproperty_participanttype>(Data[0]);
    const char *participant_type_str = icalproperty_participanttype_to_string(participant_type);
    if (participant_type_str) {
        std::cout << "Participant Type String: " << participant_type_str << std::endl;
    }

    // 2. Fuzz icalproperty_string_to_participanttype
    char *participant_string = new char[Size + 1];
    memcpy(participant_string, Data, Size);
    participant_string[Size] = '\0';
    icalproperty_participanttype participant_type_enum = icalproperty_string_to_participanttype(participant_string);
    delete[] participant_string;

    // 3. Create a dummy icalproperty for further tests
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // 4. Fuzz icalproperty_set_value_from_string
    const char *value_str = reinterpret_cast<const char*>(Data);
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalproperty_set_value_from_string with icalproperty_set_parameter_from_string
    icalproperty_set_parameter_from_string(prop, value_str, "TEXT");
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

    // 5. Fuzz icalproperty_get_value_as_string_r
    char *value_as_string = icalproperty_get_value_as_string_r(prop);
    if (value_as_string) {
        std::cout << "Value as String: " << value_as_string << std::endl;
        icalmemory_free_buffer(value_as_string);
    }

    // 6. Fuzz icalproperty_get_property_name
    const char *property_name = icalproperty_get_property_name(prop);
    if (property_name) {
        std::cout << "Property Name: " << property_name << std::endl;
    }

    // Cleanup
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_342(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
