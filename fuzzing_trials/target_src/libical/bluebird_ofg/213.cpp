#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 1) {
        return 0;
    }

    // Initialize the icalproperty structure with some default values
    icalproperty *prop = icalproperty_new(ICAL_XLICCLASS_PROPERTY);
    
    if (prop == NULL) {
        return 0; // Ensure the property is not NULL
    }

    // Use the input data to set a value to the property
    // Map the input data to a valid xlicclass value
    icalproperty_xlicclass xlicclass_value = static_cast<icalproperty_xlicclass>(data[0] % (ICAL_XLICCLASS_PUBLISHNEW + 1));
    icalproperty_set_xlicclass(prop, xlicclass_value);

    // Call the function-under-test
    icalproperty_xlicclass result = icalproperty_get_xlicclass(prop);

    // Perform a check to ensure the result is within expected range
    if (result < ICAL_XLICCLASS_NONE || result > ICAL_XLICCLASS_PUBLISHNEW) {
        // Handle unexpected result
    }

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_213(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
