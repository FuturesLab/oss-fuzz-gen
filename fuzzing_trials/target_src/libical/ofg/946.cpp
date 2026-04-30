#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>  // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_946(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty object
    if (size < 1) {
        return 0;
    }

    // Create a string from the input data
    char *str_data = (char *)malloc(size + 1);
    if (str_data == NULL) {
        return 0;
    }
    memcpy(str_data, data, size);
    str_data[size] = '\0';

    // Convert the string to an icaldatetimeperiodtype
    struct icaltimetype tt = icaltime_from_string(str_data);
    struct icaldatetimeperiodtype dtp;
    dtp.time = tt;  // Assuming we only want to set the time part for this example

    // Initialize an icalproperty object with the correct type
    icalproperty *prop = icalproperty_new_rdate(dtp);
    if (prop != NULL) {
        // Call the function-under-test
        struct icaldatetimeperiodtype result = icalproperty_get_rdate(prop);

        // Clean up
        icalproperty_free(prop);
    }

    free(str_data);
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

    LLVMFuzzerTestOneInput_946(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
