// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_convert_errors at icalcomponent.c:1168:6 in icalcomponent.h
// icalcomponent_new_vpoll at icalcomponent.c:2095:16 in icalcomponent.h
// icalcomponent_new_vpatch at icalcomponent.c:2110:16 in icalcomponent.h
// icalcomponent_new_xvote at icalcomponent.c:2105:16 in icalcomponent.h
// icalcomponent_new_xpatch at icalcomponent.c:2115:16 in icalcomponent.h
// icalcomponent_free at icalcomponent.c:172:6 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    // Create a new vPatch component
    icalcomponent *vpatch = icalcomponent_new_vpatch();
    if (vpatch) {
        // Convert errors in the vPatch component
        icalcomponent_convert_errors(vpatch);
        // Free the vPatch component
        icalcomponent_free(vpatch);
    }

    // Create a new vPoll component
    icalcomponent *vpoll = icalcomponent_new_vpoll();
    if (vpoll) {
        // Convert errors in the vPoll component
        icalcomponent_convert_errors(vpoll);
        // Free the vPoll component
        icalcomponent_free(vpoll);
    }

    // Create a new xVote component
    icalcomponent *xvote = icalcomponent_new_xvote();
    if (xvote) {
        // Convert errors in the xVote component
        icalcomponent_convert_errors(xvote);
        // Free the xVote component
        icalcomponent_free(xvote);
    }

    // Create a new xPatch component
    icalcomponent *xpatch = icalcomponent_new_xpatch();
    if (xpatch) {
        // Convert errors in the xPatch component
        icalcomponent_convert_errors(xpatch);
        // Free the xPatch component
        icalcomponent_free(xpatch);
    }

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

        LLVMFuzzerTestOneInput_22(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    