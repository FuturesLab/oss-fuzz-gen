#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_575(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;
    struct icaltimetype dtstamp;

    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    component = icalparser_parse_string(inputData);

    // Ensure component is not NULL before calling the function-under-test
    if (component != NULL) {
        // Call the function-under-test
        dtstamp = icalcomponent_get_dtstamp(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the allocated input data
    free(inputData);

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

    LLVMFuzzerTestOneInput_575(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
