#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *tempData = (char *)malloc(size + 1);
    if (tempData == NULL) {
        return 0;
    }

    // Copy the input data to the temporary buffer and null-terminate it
    memcpy(tempData, data, size);
    tempData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(tempData);

    // Free the temporary buffer
    free(tempData);

    // If the component is NULL, exit
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    struct icaldurationtype duration = icalcomponent_get_duration(component);

    // Clean up the icalcomponent
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_51(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
