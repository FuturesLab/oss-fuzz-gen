#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *comp = icalcomponent_new(static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES));

    if (!comp) {
        return 0;
    }

    // Fuzz icalcomponent_get_component_name_r
    char *component_name = icalcomponent_get_component_name_r(comp);
    if (component_name) {
        std::cout << "Component Name: " << component_name << std::endl;
        free(component_name);
    }

    // Fuzz icalcomponent_get_x_name
    const char *x_name = icalcomponent_get_x_name(comp);
    if (x_name) {
        std::cout << "X Name: " << x_name << std::endl;
    }

    // Fuzz icalcomponent_get_relcalid
    const char *relcalid = icalcomponent_get_relcalid(comp);
    if (relcalid) {
        std::cout << "Relcalid: " << relcalid << std::endl;
    }

    // Fuzz icalcomponent_get_description
    const char *description = icalcomponent_get_description(comp);
    if (description) {
        std::cout << "Description: " << description << std::endl;
    }

    // Fuzz icalcomponent_get_uid
    const char *uid = icalcomponent_get_uid(comp);
    if (uid) {
        std::cout << "UID: " << uid << std::endl;
    }

    // Fuzz icalcomponent_get_comment
    const char *comment = icalcomponent_get_comment(comp);
    if (comment) {
        std::cout << "Comment: " << comment << std::endl;
    }

    // Clean up
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_13(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
