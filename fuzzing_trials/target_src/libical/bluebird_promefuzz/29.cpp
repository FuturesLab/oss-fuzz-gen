#include <sys/stat.h>
#include <string.h>
extern "C" {
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
}

#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there is at least 1 byte to use

    // Create a new VAVAILABILITY component
    icalcomponent *vavailability = icalcomponent_new_vavailability();
    if (!vavailability) return 0;

    // Use the first byte of Data as a simple description
    char description[2] = {static_cast<char>(Data[0]), '\0'};
    icalcomponent_set_description(vavailability, description);

    // Create a new XAVAILABLE component
    icalcomponent *xavailable = icalcomponent_new_xavailable();
    if (xavailable) {
        // Set summary using the second byte of Data if available
        if (Size > 1) {
            char summary[2] = {static_cast<char>(Data[1]), '\0'};
            icalcomponent_set_summary(xavailable, summary);
        }
    }

    // Create a new XVOTE component
    icalcomponent *xvote = icalcomponent_new_xvote();
    if (xvote) {
        // Set description using the third byte of Data if available
        if (Size > 2) {
            char xvote_desc[2] = {static_cast<char>(Data[2]), '\0'};
            icalcomponent_set_description(xvote, xvote_desc);
        }
    }

    // Create a new XPATCH component
    icalcomponent *xpatch = icalcomponent_new_xpatch();
    if (xpatch) {
        // Set summary using the fourth byte of Data if available
        if (Size > 3) {
            char xpatch_summary[2] = {static_cast<char>(Data[3]), '\0'};
            icalcomponent_set_summary(xpatch, xpatch_summary);
        }
    }

    // Cleanup
    icalcomponent_free(vavailability);
    icalcomponent_free(xavailable);
    icalcomponent_free(xvote);
    icalcomponent_free(xpatch);

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

    LLVMFuzzerTestOneInput_29(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
