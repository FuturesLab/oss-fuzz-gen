#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_576(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;

    // Ensure the data is not empty and can be used to create a component
    if (size > 0) {
        // Create a temporary string to hold the data
        char *tempData = static_cast<char *>(malloc(size + 1));
        if (tempData == nullptr) {
            return 0;
        }
        memcpy(tempData, data, size);
        tempData[size] = '\0';

        // Parse the data into an icalcomponent
        component = icalparser_parse_string(tempData);

        free(tempData);
    }

    if (component != nullptr) {
        // Call the function-under-test
        struct icaltimetype dtstamp = icalcomponent_get_dtstamp(component);

        // Clean up
        icalcomponent_free(component);
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

    LLVMFuzzerTestOneInput_576(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
