#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_390(const uint8_t *data, size_t size) {
    // Create a temporary buffer to hold the input data
    char *tempData = (char *)malloc(size + 1);
    if (tempData == NULL) {
        return 0;
    }

    // Copy the input data into the temporary buffer and null-terminate it
    memcpy(tempData, data, size);
    tempData[size] = '\0';

    // Initialize an icalcomponent from the input data
    icalcomponent *component = icalparser_parse_string(tempData);

    // Free the temporary buffer
    free(tempData);

    // If the component is successfully created, call the function-under-test
    if (component != NULL) {
        const char *summary = icalcomponent_get_summary(component);

        // Free the component after use
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_normalize
        icalcomponent_normalize(component);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
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

    LLVMFuzzerTestOneInput_390(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
