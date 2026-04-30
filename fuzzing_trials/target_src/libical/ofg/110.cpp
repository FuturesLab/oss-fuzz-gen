#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Initialize a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_TZOFFSETTO_PROPERTY);

    // Ensure that the data is not empty
    if (size > 0) {
        // Convert the input data to a string
        char *data_str = (char *)malloc(size + 1);
        if (data_str == NULL) {
            icalproperty_free(prop);
            return 0;
        }
        memcpy(data_str, data, size);
        data_str[size] = '\0';

        // Set the value of the icalproperty using the input data
        icalvalue *value = icalvalue_new_string(data_str);
        icalproperty_set_value(prop, value);

        // Clean up
        free(data_str);
    }

    // Call the function under test
    int offset = icalproperty_get_tzoffsetto(prop);

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

    LLVMFuzzerTestOneInput_110(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
