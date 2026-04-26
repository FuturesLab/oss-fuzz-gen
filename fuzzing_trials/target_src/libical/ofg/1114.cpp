#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1114(const uint8_t *data, size_t size) {
    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_EXDATE_PROPERTY);

    // Ensure the data is not empty and fits within a reasonable size
    if (size > 0 && size < 1024) {
        // Create a string from the input data
        char *str = (char *)malloc(size + 1);
        if (str == NULL) {
            icalproperty_free(property);
            return 0;
        }
        memcpy(str, data, size);
        str[size] = '\0';

        // Create an icaltimetype from the string
        struct icaltimetype exdate = icaltime_from_string(str);

        // Set the exdate in the property
        icalproperty_set_exdate(property, exdate);

        // Call the function-under-test
        struct icaltimetype result = icalproperty_get_exdate(property);

        // Clean up
        free(str);
    }

    icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_1114(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
