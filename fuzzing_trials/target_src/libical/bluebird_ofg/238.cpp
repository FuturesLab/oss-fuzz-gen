#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_238(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to fill icalreqstattype
    if (size < sizeof(struct icalreqstattype)) {
        return 0;
    }

    // Initialize the icalreqstattype structure
    struct icalreqstattype reqstat;

    // Fill the icalreqstattype structure with data from the input
    reqstat.code = (icalrequeststatus)data[0]; // Corrected type to match icalrequeststatus enum

    // Allocate memory for debug and desc strings to avoid buffer overflow
    char debug_buffer[256] = {0};
    char desc_buffer[256] = {0};

    // Ensure that the debug and desc pointers do not cause buffer overflows
    // Copy data to buffers and ensure null-termination
    if (size > 1) {
        size_t debug_len = size - 1 < 255 ? size - 1 : 255;
        memcpy(debug_buffer, &data[1], debug_len);
        debug_buffer[debug_len] = '\0';
        reqstat.debug = debug_buffer;
    } else {
        reqstat.debug = nullptr;
    }

    if (size > 2) {
        size_t desc_len = size - 2 < 255 ? size - 2 : 255;
        memcpy(desc_buffer, &data[2], desc_len);
        desc_buffer[desc_len] = '\0';
        reqstat.desc = desc_buffer;
    } else {
        reqstat.desc = nullptr;
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_requeststatus(reqstat, NULL);

    // Clean up the created property
    if (property != NULL) {
        icalproperty_free(property);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_238(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
