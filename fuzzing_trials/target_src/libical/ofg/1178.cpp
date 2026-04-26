#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h> // Correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_1178(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated before using it as a string
    char *data_str = (char *)malloc(size + 1);
    if (data_str == NULL) {
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Initialize the library (if necessary)
    icalcomponent *component = icalcomponent_new_from_string(data_str);
    free(data_str);
    if (component == NULL) {
        return 0;
    }

    icalproperty *property = icalcomponent_get_first_property(component, ICAL_TZNAME_PROPERTY);
    if (property != NULL) {
        // Call the function-under-test
        const char *tzname = icalproperty_get_tzname(property);
        // Use the tzname if needed, here we just ensure the function is called
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_1178(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
