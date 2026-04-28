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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    // Initialize components
    icalcomponent *vpoll = icalcomponent_new_vpoll();
    icalcomponent *vvoter = icalcomponent_new_vvoter();
    icalcomponent *xvote = icalcomponent_new_xvote();
    icalcomponent *participant = icalcomponent_new_participant();
    icalcomponent *vreply = icalcomponent_new_vreply();

    // Add components in various combinations
    icalcomponent_add_component(vpoll, vvoter);
    icalcomponent_add_component(vpoll, xvote);
    icalcomponent_add_component(vpoll, participant);
    icalcomponent_add_component(vpoll, vreply);

    icalcomponent_add_component(vvoter, xvote);
    icalcomponent_add_component(vvoter, participant);
    icalcomponent_add_component(vvoter, vreply);

    icalcomponent_add_component(xvote, participant);
    icalcomponent_add_component(xvote, vreply);

    // Clean up components
    icalcomponent_remove_component(vpoll, vvoter);
    icalcomponent_remove_component(vpoll, xvote);
    icalcomponent_remove_component(vpoll, participant);
    icalcomponent_remove_component(vpoll, vreply);

    icalcomponent_remove_component(vvoter, xvote);
    icalcomponent_remove_component(vvoter, participant);
    icalcomponent_remove_component(vvoter, vreply);

    icalcomponent_remove_component(xvote, participant);
    icalcomponent_remove_component(xvote, vreply);

    icalcomponent_free(vpoll);
    icalcomponent_free(vvoter);
    icalcomponent_free(xvote);
    icalcomponent_free(participant);
    icalcomponent_free(vreply);

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

    LLVMFuzzerTestOneInput_99(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
