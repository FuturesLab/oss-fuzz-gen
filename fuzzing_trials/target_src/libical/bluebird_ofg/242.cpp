#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an int value
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an int value from the data
    int priority = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        priority |= data[i] << (i * 8);
    }

    // Prepare a string for extra data, ensuring it's null-terminated
    char extra_data[256] = {0}; // Use a fixed size for simplicity
    if (size > sizeof(int)) {
        size_t copy_size = size - sizeof(int);
        if (copy_size > sizeof(extra_data) - 1) {
            copy_size = sizeof(extra_data) - 1;
        }
        std::memcpy(extra_data, data + sizeof(int), copy_size);
        extra_data[copy_size] = '\0'; // Ensure null-termination
    }

    // Create a new icalparameter of type X and set its value
    icalparameter *param = icalparameter_new(ICAL_X_PARAMETER);
    if (param != nullptr) {
        icalparameter_set_x(param, extra_data);

        // Call the function-under-test
        icalproperty *property = icalproperty_vanew_priority(priority, param, nullptr);

        // Ensure the property is not freed before the parameter
        if (property != nullptr) {
            // icalproperty_vanew_priority takes ownership of the param,
            // so we should not free it manually to avoid use-after-free.
            // We should just free the property.
            icalproperty_free(property);
        } else {
            // If property creation fails, we still need to free the param
            icalparameter_free(param);
        }
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

    LLVMFuzzerTestOneInput_242(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
