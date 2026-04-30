#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    // Ensure the input size is reasonable to prevent excessive memory usage
    if (size == 0 || size > 1024) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *inputData = static_cast<char*>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Allocate memory for the icalcomponent
    icalcomponent *component = icalcomponent_new_from_string(inputData);
    
    // Free the allocated input data
    free(inputData);

    // If the component creation failed, exit early
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalproperty *property = icalcomponent_get_current_property(component);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_295(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
